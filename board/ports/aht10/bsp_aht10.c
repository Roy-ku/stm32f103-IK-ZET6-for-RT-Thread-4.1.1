#include <rtthread.h>
#include <board.h>

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "bsp_aht10"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif

#ifdef BSP_USING_AHT10

aht10_device_t aht10_dev = RT_NULL;
static int bsp_aht10_init(void);

/**
 * @brief 更新AHT10資料
 * @return int 是否成功 RT_EOK:成功 RT_ERROR:失敗
 */
int bsp_aht10_data_update(void)
{
    if (aht10_data_update(aht10_dev) != RT_EOK)
    {
        LOG_E("aht10 data update error.");
        return RT_ERROR;
    }
    return RT_EOK;
}

/**
 * @brief 輸出AHT10資料
 * @return int 是否成功 RT_EOK:成功 RT_ERROR:失敗
 */
int bsp_aht10_data_print(void)
{
    char _temperature[5] = {0};
    char _humidity[5] = {0};

    if (sprintf(_temperature, "%.2f", aht10_dev->monitor.temperature) <= 0)
    {
        return RT_ERROR;
    }
    if (sprintf(_humidity, "%.2f", aht10_dev->monitor.humidity) <= 0)
    {
        return RT_ERROR;
    }
    LOG_D("temperature: %s humidity: %s", _temperature, _humidity);
    return RT_EOK;
}

/**
 * @brief 初始化 AHT10
 * @return int 是否成功 RT_EOK:成功 RT_ERROR:失敗
 */
static int bsp_aht10_init(void)
{
    aht10_dev = aht10_init(AHT10_I2C_BUS, RT_NULL);
    return RT_EOK;
}
#ifdef FINSH_USING_MSH
INIT_DEVICE_EXPORT(bsp_aht10_init);
#endif /* FINSH_USING_MSH */

#endif /* BSP_USING_AHT10 */
