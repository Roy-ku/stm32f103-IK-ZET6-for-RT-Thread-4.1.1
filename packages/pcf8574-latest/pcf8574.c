/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-21     SummerGift   first version
 * 2018-11-22     flybreak     Make the first version of pcf8574's package
 */

#include "pcf8574.h"

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "pcf8574"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif
#ifdef PKG_USING_PCF8574

#define PCF8574T_CLEAR_BIT(x, bit) (x &= ~(1 << bit))      /* 清零第bit位 */
#define PCF8574T_SET_BIT(x, bit) (x |= (1 << bit))         /* 置位第bit位 */
#define PCF8574T_TOGGLE_BIT(x, bit) (x ^= (1 << bit))      /* 反轉第bit位 */
#define PCF8574T_GET_BIT(x, bit) ((x & (1 << bit)) >> bit) /* 獲取第bit位 */

static rt_uint8_t pcf8574_port_read(pcf8574_device_t dev);
static void pcf8574_port_write(pcf8574_device_t dev, rt_uint8_t port_val);

/**
 * This function read the data port of pcf8574.
 *
 * @param dev the pointer of device structure
 *
 * @return the state of data port. 0xFF meas all pin is high.
 */
static rt_uint8_t pcf8574_port_read(pcf8574_device_t dev)
{
    rt_uint8_t value;

    rt_device_read(&dev->bus->parent, dev->i2c_addr, &value, 1);

    return value;
}

/**
 * This function sets the status of the data port.
 *
 * @param dev the pointer of device structure
 * @param port_val the port value you want to set, 0xFF meas all pin output high.
 */
static void pcf8574_port_write(pcf8574_device_t dev, rt_uint8_t value)
{
    rt_device_write(&dev->bus->parent, dev->i2c_addr, &value, 1);
}

/**
 * This function read the specified port pin of the pcf8574.
 *
 * @param dev the pointer of device structure
 * @param pin the specified pin of the data port
 *
 * @return the status of the specified data port pin, 0 is low, 1 is high.
 */
rt_uint8_t pcf8574_pin_read(pcf8574_device_t dev, rt_uint8_t pin)
{
    rt_uint8_t data;
    data = pcf8574_port_read(dev);

    if (PCF8574T_GET_BIT(data, pin))
        return 1;
    else
        return 0;
}

/**
 * This function sets the status of the specified port pin.
 *
 * @param dev the pointer of device structure
 * @param pin_val the specified pin value you want to set, 0 is low, 1 is high.
 */
void pcf8574_pin_write(pcf8574_device_t dev, rt_uint8_t pin, rt_uint8_t pin_val)
{
    rt_uint8_t data;
    data = pcf8574_port_read(dev);

    if (pin_val == 0)
        // data &= ~(1 << pin);
        PCF8574T_CLEAR_BIT(data, pin);
    else
        // data |= 1 << pin;
        PCF8574T_SET_BIT(data, pin);

    pcf8574_port_write(dev, data);
}

/**
 * This function initialize the pcf8574 device.
 *
 * @param dev_name the name of i2c bus device
 * @param i2c_addr the i2c device address for i2c communication,RT_NULL use default address
 *
 * @return the pointer of device structure, RT_NULL reprensents  initialization failed.
 */
pcf8574_device_t pcf8574_init(const char *dev_name, rt_uint8_t i2c_addr)
{
    rt_uint8_t buffer[] = {0xFF};
    pcf8574_device_t dev = RT_NULL;

    RT_ASSERT(dev_name);

    dev = rt_calloc(1, sizeof(struct pcf8574_device));
    if (dev == RT_NULL)
    {
        rt_kprintf("Can't allocate memory for pcf8574 device on '%s' \r\n", dev_name);
        goto __exit;
    }

    dev->bus = (struct rt_i2c_bus_device *)rt_device_find(dev_name);
    if (dev->bus == RT_NULL)
    {
        rt_kprintf("i2c_bus %s for PCF8574 not found!\r\n", dev_name);
        goto __exit;
    }

    if (i2c_addr != RT_NULL)
        dev->i2c_addr = i2c_addr;
    else
        dev->i2c_addr = PCF8574_ADDR_DEFAULT;

    if (rt_device_open(&dev->bus->parent, RT_NULL) != RT_EOK)
    {
        rt_kprintf("i2c_bus %s for PCF8574 opened failed!\r\n", dev_name);
        goto __exit;
    }

    /* 讓 pcf8574 所有PIN預設為 HIGH */
    rt_device_write(&dev->bus->parent, dev->i2c_addr, &buffer, 1);

    rt_kprintf("pcf8574(%s) init.\r\n", dev_name);
    return dev;

__exit:
    if (dev != RT_NULL)
    {
        rt_device_close(&dev->bus->parent);
        rt_free(dev);
    }
    return RT_NULL;
}

/**
 * This function releases memory
 *
 * @param dev the pointer of device structure
 */
void pcf8574_deinit(struct pcf8574_device *dev)
{
    RT_ASSERT(dev);
    rt_device_close(&dev->bus->parent);
    rt_free(dev);
}
#endif /* PKG_USING_PCF8574 */
