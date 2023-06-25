#include <rtthread.h>
#include <board.h>

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "bsp_at24cxx"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif

#ifdef BSP_USING_AT24CXX
at24cxx_device_t at24cxx_dev = RT_NULL;
static int bsp_atc24xx_init(void);

static int bsp_atc24xx_init(void)
{
	    at24cxx_dev = at24cxx_init(PCF8574_I2C_BUS, RT_NULL);

    if (at24cxx_dev == RT_NULL)
        return RT_EOK;
    return RT_ERROR;
}
#ifdef FINSH_USING_MSH
INIT_DEVICE_EXPORT(bsp_atc24xx_init);
#endif /* FINSH_USING_MSH */

#endif /* BSP_USING_AT24CXX */
