/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-22     flybreak     Make the first version of pcf8574's package
 */

#include <rtthread.h>
#include "pcf8574.h"
#include <stdlib.h>

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "bsp_pcf8574"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif
#ifdef BSP_USING_PCF8574

#define TEST_IO pcf8574_P0 //(0-7)

pcf8574_device_t pcf8574_dev = RT_NULL;
static int bsp_pcf8574_init(void);
static int bsp_pcf8574_init(void)
{
    pcf8574_dev = pcf8574_init(PCF8574_I2C_BUS, RT_NULL);

    if (pcf8574_dev == RT_NULL)
        return RT_EOK;
    return RT_ERROR;
}
#ifdef FINSH_USING_MSH
INIT_DEVICE_EXPORT(bsp_pcf8574_init);
#endif /* FINSH_USING_MSH */

int bsp_pcf8574_sample(void)
{
    rt_uint8_t value;

    pcf8574_pin_write(pcf8574_dev, TEST_IO, 0);

    value = pcf8574_pin_read(pcf8574_dev, TEST_IO);
    LOG_D("The value of pcf8574.P%d is %d", TEST_IO, value);

    rt_thread_mdelay(1000);

    pcf8574_pin_write(pcf8574_dev, TEST_IO, 1);

    value = pcf8574_pin_read(pcf8574_dev, TEST_IO);
    LOG_D("The value of pcf8574.P%d is %d", TEST_IO, value);

    // pcf8574_deinit(pcf8574_dev);

    return RT_EOK;
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(bsp_pcf8574_sample, a pcf8574 sample);
#endif

int bsp_pcf8574_toggle(int argc, char *argv[])
{
    rt_int8_t pin = 0;
    // LOG_D("input para is: %s %s", argv[0], argv[1]);
    if (argc != 2)
    {
        LOG_D("error cmd! please input a parameter");
        return RT_ERROR;
    }
    else
    {
        pin = atoi(argv[1]);
        if (pin >= 0 || pin <= 7)
        {
            pcf8574_pin_toggle(pcf8574_dev, (pcf8574_pin_t)pin);
        }
        else
        {
            LOG_D("error cmd! please [0..7]");
            return RT_ERROR;
        }
    }
    return RT_EOK;
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(bsp_pcf8574_toggle, a pcf8574 toggle <pin>);
#endif
#endif /* BSP_USING_PCF8574 */
