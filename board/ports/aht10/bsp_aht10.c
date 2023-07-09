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
static int bsp_aht10_update(void);
static int bsp_aht10_init(void);

static int bsp_aht10_update(void)
{
    char _temperature[5] = {0};
    char _humidity[5] = {0};

    if (aht10_read_temphum(aht10_dev) == RT_EOK)
    {
        if (sprintf(_temperature, "%.2f", aht10_dev->monitor.temperature) <= 0)
        {
            return RT_ERROR;
        }
        if (sprintf(_humidity, "%.2f", aht10_dev->monitor.humidity) <= 0)
        {
            return RT_ERROR;
        }
        LOG_D("temperature: %s humidity: %s", _temperature, _humidity);
    }
    return RT_EOK;
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(bsp_aht10_update, update temperature and humidity);
#endif /* FINSH_USING_MSH */

// static int bsp_aht10_read_humidity(void)
// {
//     char buf[10];
//     aht10_dev->monitor.humidity = aht10_read_humidity(aht10_dev);

//     if (sprintf(buf, "%.2f", aht10_dev->monitor.humidity) > 0)
//     {
//         LOG_D("humidity: %s\r\n", buf);
//         return RT_EOK;
//     }
//     return RT_ERROR;
// }
// #ifdef FINSH_USING_MSH
// MSH_CMD_EXPORT(bsp_aht10_read_humidity, read humidity function);
// #endif /* FINSH_USING_MSH */

static int bsp_aht10_init(void)
{
    aht10_dev = aht10_init(AHT10_I2C_BUS, RT_NULL);

    if (aht10_dev == RT_NULL)
        return RT_EOK;
    return RT_ERROR;
}
#ifdef FINSH_USING_MSH
INIT_DEVICE_EXPORT(bsp_aht10_init);
#endif /* FINSH_USING_MSH */

#endif /* BSP_USING_AHT10 */
