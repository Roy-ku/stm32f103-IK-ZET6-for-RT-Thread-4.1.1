#include <rtthread.h>
#include <board.h>

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "drv_esp01s"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif

#ifdef BSP_USING_ESP01S

/* 用於創建ESP01s通信線程 */
struct rt_thread esp01s_thread;
rt_uint8_t esp01s_thread_stack[ESP01S_THREAD_STACK_SIZE];

/* 用於接收消息的信號量 */
static struct rt_semaphore esp01s_sem;
static rt_device_t esp01s_serial;

static rt_err_t uart_rx_ind(rt_device_t dev, rt_size_t size);
static char uart_get_char(void);
static void data_parsing_thread_entry(void *parameter);
static int user_esp01s_init(void);

/* 接收數據回調函數 */
static rt_err_t uart_rx_ind(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到數據後產生中斷，調用此回調函數，然後發送接收信號量 */
    if (size > 0)
    {
        rt_sem_release(&esp01s_sem);
    }
    return RT_EOK;
}

static char uart_get_char(void)
{
    char ch;

    while (rt_device_read(esp01s_serial, 0, &ch, 1) == 0)
    {
        rt_sem_control(&esp01s_sem, RT_IPC_CMD_RESET, RT_NULL);
        rt_sem_take(&esp01s_sem, RT_WAITING_FOREVER);
    }
    return ch;
}

/* 数据解析线程 */
static void data_parsing_thread_entry(void *parameter)
{
    char ch;
    char data[ONE_DATA_MAXLEN];
    static char i = 0;

    while (1)
    {
        ch = uart_get_char();
        //rt_device_write(esp01s_serial, 0, &ch, 1);
        if (ch == DATA_CMD_END)
        {
            data[i++] = '\0';
            LOG_D("data=%s", data);
            i = 0;
            continue;
        }
        i = (i >= ONE_DATA_MAXLEN - 1) ? ONE_DATA_MAXLEN - 1 : i;
        data[i++] = ch;
    }
}

static int user_esp01s_init(void)
{
    rt_err_t ret = RT_EOK;
    char uart_name[RT_NAME_MAX];
    char str[] = "AT\r\n";

    rt_strncpy(uart_name, ESP01S_UART_NAME, RT_NAME_MAX);

    /* 查找系統中的串口設備 */
    esp01s_serial = rt_device_find(uart_name);
    if (!esp01s_serial)
    {
        rt_kprintf("find %s failed!\r\n", uart_name);
        return RT_ERROR;
    }

    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate  =  BAUD_RATE_9600;
    if(RT_EOK != rt_device_control(esp01s_serial, RT_DEVICE_CTRL_CONFIG, &config))
    {
        rt_kprintf("[%s] config change failed!\n", uart_name);
    }

    /* 初始化信號量 */
    rt_sem_init(&esp01s_sem, "esp01s_sem", 0, RT_IPC_FLAG_FIFO);
    /* 以中斷接收及輪詢發送模式打開串口設備 */
    rt_device_open(esp01s_serial, RT_DEVICE_FLAG_INT_RX);
    /* 設置接收回調函數 */
    rt_device_set_rx_indicate(esp01s_serial, uart_rx_ind);
    /* 發送字符串 */
    rt_device_write(esp01s_serial, 0, str, (sizeof(str) - 1));

    /* 創建 esp01s 線程 */
    if (rt_thread_init(&esp01s_thread, "esp01s", data_parsing_thread_entry, RT_NULL,
                       &esp01s_thread_stack[0],
                       sizeof(esp01s_thread_stack),
                       ESP01S_THREAD_PRIORITY, ESP01S_THREAD_TIMESLICE) == RT_EOK)
    {
        rt_thread_startup(&esp01s_thread);
    }
    else
    {
        rt_kprintf("esp01s_thread init failed!\r\n");
        return RT_ERROR;
    }
    rt_kprintf("esp01s init.\r\n");
    return RT_EOK;
}

#ifdef FINSH_USING_MSH
INIT_DEVICE_EXPORT(user_esp01s_init);
#endif /* FINSH_USING_MSH */

#endif /* BSP_USING_ESP01S */
