/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "mian"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif

MSG_T msg;

struct rt_thread led_thread;
rt_uint8_t rt_led_thread_stack[256];

void led_task_entry(void *parameter);

int main(void)
{

    // 初始化LED線程
    rt_thread_init(&led_thread, "led", led_task_entry, RT_NULL, &rt_led_thread_stack[0], sizeof(rt_led_thread_stack), 10, 20);
    // 開啟線程調度
    rt_thread_startup(&led_thread);

    LoadParam();
    while (1)
    {
        //led_config(LED_1,ON);

        if (MQ_GetMsg(&msg))
        {
            rt_uint8_t data = 0;
            switch (msg.MsgCode)
            {
            case MSG_Btn2:
                LOG_D("MSG_Btn2");
                break;
            case MSG_Btn3:
                LOG_D("MSG_Btn3");
                break;
            case MSG_PCF8574_INT:
                data = pcf8574_port_read(pcf8574_dev);
                LOG_D("data = %x", data);
                rt_pin_irq_enable(PCF8574_INT_PIN, PIN_IRQ_ENABLE);
                break;
            case MSG_AHT10_UPDATE:
                // LOG_D("MSG_AHT10_UPDATE");
                bsp_aht10_data_update();
                bsp_aht10_data_print();
                break;
            default:
                break;
            }
        }
         led_config(LED_1,OFF);
    }
}

void led_task_entry(void *parameter)
{
    // rt_uint8_t major, minor;
    while (1)
    {
        // cpu_usage_get(&major, &minor);
        // LOG_D("cpu usage: %u.%u%%  ", major, minor);
        //led_config(LED_2, TOGGLE);
        rt_thread_delay(200);
    }
}
