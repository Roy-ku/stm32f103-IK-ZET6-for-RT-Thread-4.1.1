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

#ifdef BSP_USING_PCF8574

#define TEST_IO 0 //(0-7)

pcf8574_device_t dev = RT_NULL;
static int pcf8574_set(void);
static int pcf8574_set(void)
{
    dev = pcf8574_init(PCF8574_I2C_BUS, RT_NULL);

    if (dev == RT_NULL)
        return RT_EOK;
    return RT_ERROR;
}
#ifdef FINSH_USING_MSH
INIT_DEVICE_EXPORT(pcf8574_set);
#endif /* FINSH_USING_MSH */

int pcf8574_sample(void)
{
    rt_uint8_t value;

    pcf8574_pin_write(dev, TEST_IO, 0);

    value = pcf8574_pin_read(dev, TEST_IO);
    rt_kprintf("The value of pcf8574.P%d is %d\n", TEST_IO, value);

    rt_thread_mdelay(1000);

    pcf8574_pin_write(dev, TEST_IO, 1);

    value = pcf8574_pin_read(dev, TEST_IO);
    rt_kprintf("The value of pcf8574.P%d is %d\n", TEST_IO, value);

    // pcf8574_deinit(dev);

    return RT_EOK;
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(pcf8574_sample, a pcf8574 sample);
#endif
#endif /* BSP_USING_PCF8574 */
