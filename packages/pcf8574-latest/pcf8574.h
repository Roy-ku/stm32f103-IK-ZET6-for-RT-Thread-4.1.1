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
#include <board.h>

#ifdef PKG_USING_PCF8574

#define PCF8574_ADDR_DEFAULT 0x20
#define PCF8574_I2C_BUS "i2c1"
/* defined the PCF8574 INT pin: PG6 */
#define PCF8574_INT_PIN GET_PIN(G, 9)

typedef enum
{
    pcf8574_P0 = 0,
    pcf8574_P1,
    pcf8574_P2,
    pcf8574_P3,
    pcf8574_P4,
    pcf8574_P5,
    pcf8574_P6,
    pcf8574_P7
} pcf8574_pin_t;

/* pcf8574 device structure */
struct pcf8574_device
{
    struct rt_i2c_bus_device *bus;
    rt_uint8_t i2c_addr;
};
typedef struct pcf8574_device *pcf8574_device_t;
extern pcf8574_device_t pcf8574_dev;

rt_uint8_t pcf8574_port_read(pcf8574_device_t dev);
void pcf8574_port_write(pcf8574_device_t dev, rt_uint8_t port_val);
void pcf8574_pin_toggle(pcf8574_device_t dev, pcf8574_pin_t pin);
pcf8574_device_t pcf8574_init(const char *dev_name, rt_uint8_t i2c_addr);
void pcf8574_deinit(struct pcf8574_device *dev);
rt_uint8_t pcf8574_pin_read(pcf8574_device_t dev, pcf8574_pin_t pin);
void pcf8574_pin_write(pcf8574_device_t dev, pcf8574_pin_t pin, rt_uint8_t pin_val);

#endif /* PKG_USING_PCF8574 */
#endif /* __PCF8574_H */
