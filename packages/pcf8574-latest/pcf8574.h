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

#ifndef __PCF8574_H
#define __PCF8574_H

#include <rtthread.h>
#include <rtdevice.h>

#ifdef  PKG_USING_PCF8574

#define PCF8574_ADDR_DEFAULT    0x20
#define PCF8574_I2C_BUS "i2c1"

typedef enum
{
    P0 = 0,
    P1,
    P2,
    P3,
    P4,
    P5,
    P6,
    P7
} pcf8574_pin_t;

/* pcf8574 device structure */
struct pcf8574_device
{
    struct rt_i2c_bus_device *bus;
    rt_uint8_t i2c_addr;
};
typedef struct pcf8574_device *pcf8574_device_t;

void pcf8574_pin_toggle(pcf8574_device_t dev, pcf8574_pin_t pin);
pcf8574_device_t pcf8574_init(const char *dev_name, rt_uint8_t i2c_addr);
void pcf8574_deinit(struct pcf8574_device *dev);
rt_uint8_t pcf8574_pin_read(pcf8574_device_t dev, pcf8574_pin_t pin);
void pcf8574_pin_write(pcf8574_device_t dev, pcf8574_pin_t pin, rt_uint8_t pin_val);

#endif /* PKG_USING_PCF8574 */
#endif /* __PCF8574_H */

