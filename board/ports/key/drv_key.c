#include <rtthread.h>
#include "flexible_button.h"
#include <stdint.h>
#include <rtdevice.h>
#include <board.h>

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "drv_key"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif

#define PIN_KEY1 GET_PIN(E, 2)
#define PIN_KEY2 GET_PIN(E, 3)
#define PIN_KEY3 GET_PIN(E, 4)
#define PIN_KEY4 GET_PIN(E, 5)
#define PIN_TOUKEY GET_PIN(E, 1)
#define PIN_WAUPKEY GET_PIN(A, 0)

typedef enum
{
    USER_BUTTON_0 = 0,
    USER_BUTTON_1,
    USER_BUTTON_2,
    USER_BUTTON_3,
    USER_BUTTON_4,
    USER_BUTTON_5,
    USER_BUTTON_MAX
} user_button_t;

static flex_button_t user_button[USER_BUTTON_MAX];

static void btn_1_cb(flex_button_t *btn)
{
    switch (btn->event)
    {
    case FLEX_BTN_PRESS_DOWN:
        LOG_D("btn_1_cb [FLEX_BTN_PRESS_DOWN]");
        break;
    case FLEX_BTN_PRESS_CLICK:
        LOG_D("btn_1_cb [FLEX_BTN_PRESS_CLICK]");
        break;
    case FLEX_BTN_PRESS_DOUBLE_CLICK:
        LOG_D("btn_1_cb [FLEX_BTN_PRESS_DOUBLE_CLICK]");
        break;
    case FLEX_BTN_PRESS_SHORT_START:
        LOG_D("btn_1_cb [FLEX_BTN_PRESS_SHORT_START]");
        break;
    case FLEX_BTN_PRESS_SHORT_UP:
        LOG_D("btn_1_cb [FLEX_BTN_PRESS_SHORT_UP]");
        break;
    case FLEX_BTN_PRESS_LONG_START:
        LOG_D("btn_1_cb [FLEX_BTN_PRESS_LONG_START]");
        break;
    case FLEX_BTN_PRESS_LONG_UP:
        LOG_D("btn_1_cb [FLEX_BTN_PRESS_LONG_UP]");
        break;
    case FLEX_BTN_PRESS_LONG_HOLD:
        LOG_D("btn_1_cb [FLEX_BTN_PRESS_LONG_HOLD]");
        break;
    case FLEX_BTN_PRESS_LONG_HOLD_UP:
        LOG_D("btn_1_cb [FLEX_BTN_PRESS_LONG_HOLD_UP]");
        break;
    }
}

static void btn_2_cb(flex_button_t *btn)
{
    switch (btn->event)
    {
    case FLEX_BTN_PRESS_DOWN:
        LOG_D("btn_2_cb [FLEX_BTN_PRESS_DOWN]");
        break;
    case FLEX_BTN_PRESS_CLICK:
        LOG_D("btn_2_cb [FLEX_BTN_PRESS_CLICK]");
        MQ_PutMsg(MSG_Btn2,0);
        break;
    case FLEX_BTN_PRESS_DOUBLE_CLICK:
        LOG_D("btn_2_cb [FLEX_BTN_PRESS_DOUBLE_CLICK]");
        break;
    case FLEX_BTN_PRESS_SHORT_START:
        LOG_D("btn_2_cb [FLEX_BTN_PRESS_SHORT_START]");
        break;
    case FLEX_BTN_PRESS_SHORT_UP:
        LOG_D("btn_2_cb [FLEX_BTN_PRESS_SHORT_UP]");
        break;
    case FLEX_BTN_PRESS_LONG_START:
        LOG_D("btn_2_cb [FLEX_BTN_PRESS_LONG_START]");
        break;
    case FLEX_BTN_PRESS_LONG_UP:
        LOG_D("btn_2_cb [FLEX_BTN_PRESS_LONG_UP]");
        break;
    case FLEX_BTN_PRESS_LONG_HOLD:
        LOG_D("btn_2_cb [FLEX_BTN_PRESS_LONG_HOLD]");
        break;
    case FLEX_BTN_PRESS_LONG_HOLD_UP:
        LOG_D("btn_2_cb [FLEX_BTN_PRESS_LONG_HOLD_UP]");
        break;
    }
}

static void btn_3_cb(flex_button_t *btn)
{
    switch (btn->event)
    {
    case FLEX_BTN_PRESS_DOWN:
        LOG_D("btn_3_cb [FLEX_BTN_PRESS_DOWN]");
        MQ_PutMsg(MSG_Btn3,0);
        break;
    case FLEX_BTN_PRESS_CLICK:
        LOG_D("btn_3_cb [FLEX_BTN_PRESS_CLICK]");
        break;
    case FLEX_BTN_PRESS_DOUBLE_CLICK:
        LOG_D("btn_3_cb [FLEX_BTN_PRESS_DOUBLE_CLICK]");
        break;
    case FLEX_BTN_PRESS_SHORT_START:
        LOG_D("btn_3_cb [FLEX_BTN_PRESS_SHORT_START]");
        break;
    case FLEX_BTN_PRESS_SHORT_UP:
        LOG_D("btn_3_cb [FLEX_BTN_PRESS_SHORT_UP]");
        break;
    case FLEX_BTN_PRESS_LONG_START:
        LOG_D("btn_3_cb [FLEX_BTN_PRESS_LONG_START]");
        break;
    case FLEX_BTN_PRESS_LONG_UP:
        LOG_D("btn_3_cb [FLEX_BTN_PRESS_LONG_UP]");
        break;
    case FLEX_BTN_PRESS_LONG_HOLD:
        LOG_D("btn_3_cb [FLEX_BTN_PRESS_LONG_HOLD]");
        break;
    case FLEX_BTN_PRESS_LONG_HOLD_UP:
        LOG_D("btn_3_cb [FLEX_BTN_PRESS_LONG_HOLD_UP]");
        break;
    }
}

static void btn_4_cb(flex_button_t *btn)
{
    switch (btn->event)
    {
    case FLEX_BTN_PRESS_DOWN:
        LOG_D("btn_4_cb [FLEX_BTN_PRESS_DOWN]");
        break;
    case FLEX_BTN_PRESS_CLICK:
        LOG_D("btn_4_cb [FLEX_BTN_PRESS_CLICK]");
        break;
    case FLEX_BTN_PRESS_DOUBLE_CLICK:
        LOG_D("btn_4_cb [FLEX_BTN_PRESS_DOUBLE_CLICK]");
        break;
    case FLEX_BTN_PRESS_SHORT_START:
        LOG_D("btn_4_cb [FLEX_BTN_PRESS_SHORT_START]");
        break;
    case FLEX_BTN_PRESS_SHORT_UP:
        LOG_D("btn_4_cb [FLEX_BTN_PRESS_SHORT_UP]");
        break;
    case FLEX_BTN_PRESS_LONG_START:
        LOG_D("btn_4_cb [FLEX_BTN_PRESS_LONG_START]");
        break;
    case FLEX_BTN_PRESS_LONG_UP:
        LOG_D("btn_4_cb [FLEX_BTN_PRESS_LONG_UP]");
        break;
    case FLEX_BTN_PRESS_LONG_HOLD:
        LOG_D("btn_4_cb [FLEX_BTN_PRESS_LONG_HOLD]");
        break;
    case FLEX_BTN_PRESS_LONG_HOLD_UP:
        LOG_D("btn_4_cb [FLEX_BTN_PRESS_LONG_HOLD_UP]");
        break;
    }
}

static void btn_toukey_cb(flex_button_t *btn)
{
    switch (btn->event)
    {
    case FLEX_BTN_PRESS_DOWN:
        LOG_D("btn_toukey_cb [FLEX_BTN_PRESS_DOWN]");
        break;
    case FLEX_BTN_PRESS_CLICK:
        LOG_D("btn_toukey_cb [FLEX_BTN_PRESS_CLICK]");
        break;
    case FLEX_BTN_PRESS_DOUBLE_CLICK:
        LOG_D("btn_toukey_cb [FLEX_BTN_PRESS_DOUBLE_CLICK]");
        break;
    case FLEX_BTN_PRESS_SHORT_START:
        LOG_D("btn_toukey_cb [FLEX_BTN_PRESS_SHORT_START]");
        break;
    case FLEX_BTN_PRESS_SHORT_UP:
        LOG_D("btn_4_cb [FLEX_BTN_PRESS_SHORT_UP]");
        break;
    case FLEX_BTN_PRESS_LONG_START:
        LOG_D("btn_toukey_cb [FLEX_BTN_PRESS_LONG_START]");
        break;
    case FLEX_BTN_PRESS_LONG_UP:
        LOG_D("btn_toukey_cb [FLEX_BTN_PRESS_LONG_UP]");
        break;
    case FLEX_BTN_PRESS_LONG_HOLD:
        // LOG_D("btn_toukey_cb [FLEX_BTN_PRESS_LONG_HOLD]");
        break;
    case FLEX_BTN_PRESS_LONG_HOLD_UP:
        // LOG_D("btn_toukey_cb [FLEX_BTN_PRESS_LONG_HOLD_UP]");
        break;
    }
}

static void btn_waupkey_cb(flex_button_t *btn)
{
    switch (btn->event)
    {
        //        case FLEX_BTN_PRESS_DOWN:
        //            LOG_D("btn_waupkey_cb [FLEX_BTN_PRESS_DOWN]");
        //            break;
    case FLEX_BTN_PRESS_CLICK:
        LOG_D("btn_waupkey_cb [FLEX_BTN_PRESS_CLICK]");
        break;
        //        case FLEX_BTN_PRESS_DOUBLE_CLICK:
        //            LOG_D("btn_waupkey_cb [FLEX_BTN_PRESS_DOUBLE_CLICK]");
        //            break;
        //        case FLEX_BTN_PRESS_SHORT_START:
        //            LOG_D("btn_waupkey_cb [FLEX_BTN_PRESS_SHORT_START]");
        //            break;
    case FLEX_BTN_PRESS_SHORT_UP:
        LOG_D("btn_waupkey_cb [FLEX_BTN_PRESS_CLICK]");
        break;
        //        case FLEX_BTN_PRESS_LONG_START:
        //            LOG_D("btn_waupkey_cb [FLEX_BTN_PRESS_LONG_START]");
        //            break;
    case FLEX_BTN_PRESS_LONG_UP:
        LOG_D("btn_waupkey_cb [FLEX_BTN_PRESS_CLICK]");
        break;
        //        case FLEX_BTN_PRESS_LONG_HOLD:
        //             LOG_D("btn_waupkey_cb [FLEX_BTN_PRESS_LONG_HOLD]");
        //            break;
    case FLEX_BTN_PRESS_LONG_HOLD_UP:
        LOG_D("btn_waupkey_cb [FLEX_BTN_PRESS_CLICK]");
        break;
    }
}

static uint8_t button_key1_read(void)
{
    return rt_pin_read(PIN_KEY1);
}

static uint8_t button_key2_read(void)
{
    return rt_pin_read(PIN_KEY2);
}

static uint8_t button_key3_read(void)
{
    return rt_pin_read(PIN_KEY3);
}

static uint8_t button_key4_read(void)
{
    return rt_pin_read(PIN_KEY4);
}

static uint8_t button_toukey_read(void)
{
    return rt_pin_read(PIN_TOUKEY);
}

static uint8_t button_waupkey_read(void)
{
    return rt_pin_read(PIN_WAUPKEY);
}

static void button_scan(void *arg)
{
    while (1)
    {
        flex_button_scan();
        rt_thread_mdelay(20);
    }
}

static void user_button_init(void)
{
    int i;

    rt_memset(&user_button[0], 0x0, sizeof(user_button));

    user_button[USER_BUTTON_0].usr_button_read = button_key1_read;
    user_button[USER_BUTTON_0].cb = (flex_button_response_callback)btn_1_cb;

    user_button[USER_BUTTON_1].usr_button_read = button_key2_read;
    user_button[USER_BUTTON_1].cb = (flex_button_response_callback)btn_2_cb;

    user_button[USER_BUTTON_2].usr_button_read = button_key3_read;
    user_button[USER_BUTTON_2].cb = (flex_button_response_callback)btn_3_cb;

    user_button[USER_BUTTON_3].usr_button_read = button_key4_read;
    user_button[USER_BUTTON_3].cb = (flex_button_response_callback)btn_4_cb;

    user_button[USER_BUTTON_4].usr_button_read = button_toukey_read;
    user_button[USER_BUTTON_4].cb = (flex_button_response_callback)btn_toukey_cb;

    user_button[USER_BUTTON_5].usr_button_read = button_waupkey_read;
    user_button[USER_BUTTON_5].cb = (flex_button_response_callback)btn_waupkey_cb;

    rt_pin_mode(PIN_KEY1, PIN_MODE_INPUT_PULLUP);      /* set KEY pin mode to input */
    rt_pin_mode(PIN_KEY2, PIN_MODE_INPUT_PULLUP);      /* set KEY pin mode to input */
    rt_pin_mode(PIN_KEY3, PIN_MODE_INPUT_PULLUP);      /* set KEY pin mode to input */
    rt_pin_mode(PIN_KEY4, PIN_MODE_INPUT_PULLUP);      /* set KEY pin mode to input */
    rt_pin_mode(PIN_TOUKEY, PIN_MODE_INPUT_PULLUP);    /* set KEY pin mode to input */
    rt_pin_mode(PIN_WAUPKEY, PIN_MODE_INPUT_PULLDOWN); /* set KEY pin mode to input */

    for (i = 0; i < USER_BUTTON_MAX; i++)
    {
        user_button[i].pressed_logic_level = 0;
        user_button[i].click_start_tick = 10;
        user_button[i].short_press_start_tick = 50;
        user_button[i].long_press_start_tick = 200;
        user_button[i].long_hold_start_tick = 400;

        if (i == USER_BUTTON_4)
        {
            user_button[USER_BUTTON_4].pressed_logic_level = 1;
        }
        if (i == USER_BUTTON_5)
        {
            user_button[USER_BUTTON_5].pressed_logic_level = 1;
        }

        flex_button_register(&user_button[i]);
    }
}

int flex_button_main(void)
{
    rt_thread_t tid = RT_NULL;

    user_button_init();

    /* Create background ticks thread */
    tid = rt_thread_create("flex_btn", button_scan, RT_NULL, 256, 5, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    rt_kprintf("flex_btn init.\r\n");
    return RT_EOK;
}
#ifdef FINSH_USING_MSH
INIT_DEVICE_EXPORT(flex_button_main);
#endif
