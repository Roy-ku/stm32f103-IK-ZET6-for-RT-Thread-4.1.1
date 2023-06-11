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

    while (1)
    {
        // led_config(LED_1, ON);
        // rt_thread_mdelay(500);
        // led_config(LED_1, OFF);
        // rt_thread_mdelay(500);
        LOG_D("enter main thread.");
        if (MQ_GetMsg(&msg))
        {
            switch (msg.MsgCode)
            {
            case MSG_Btn2:
                LOG_D("MSG_Btn2");
                break;
            case MSG_Btn3:
                LOG_D("MSG_Btn3");
                break;
            default:
                break;
            }
        }
    }
}

void led_task_entry(void *parameter)
{
    while (1)
    {
        led_config(LED_2, TOGGLE);
        rt_thread_delay(1000);
        // led_config(LED_2, OFF);
        // rt_thread_delay(1000);
    }
}
