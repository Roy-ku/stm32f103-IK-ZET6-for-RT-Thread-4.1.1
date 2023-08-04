/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <stm32f1xx.h>
#include "drv_common.h"
#include "bsp_timer.h"
#include "drv_gpio.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_esp01s.h"
#include "bsp_pcf8574.h"
#include "bsp_MessageQueue.h"
#include "bsp_at24cxx.h"
#include "bsp_aht10.h"
#include "bsp_i2c_tool.h"
#include "rt_cpu_usage.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define STM32_FLASH_START_ADRESS ((uint32_t)0x8008000)
#define STM32_FLASH_SIZE (480 * 1024)
#define STM32_FLASH_END_ADDRESS ((uint32_t)(STM32_FLASH_START_ADRESS + STM32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] <8-64>, Default: 64*/
#define STM32_SRAM_SIZE 64
#define STM32_SRAM_END (0x20000000 + STM32_SRAM_SIZE * 1024)

#if defined(__ARMCC_VERSION)
    extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section = "CSTACK"
#define HEAP_BEGIN (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN ((void *)&__bss_end)
#endif

#define HEAP_END STM32_SRAM_END

    void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
