#include <rtthread.h>
#include <stdint.h>
#include <rtdevice.h>
#include <board.h>

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "bsp_led"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif

/* defined the LED1 pin: PG6 */
#define PIN_LED1 GET_PIN(G, 6)
/* defined the LED2 pin: PA8 */
#define PIN_LED2 GET_PIN(A, 8)
/* defined the LED3 pin: PB8 */
#define PIN_LED3 GET_PIN(B, 8)
/* defined the LED4 pin: PB9 */
#define PIN_LED4 GET_PIN(B, 9)

void led_config(user_led_t led, user_led_state_t state)
{
    switch (led)
    {
    case LED_1:
        if (state == ON)
        {
            rt_pin_write(PIN_LED1, PIN_LOW);
        }
        else if (state == OFF)
        {
            rt_pin_write(PIN_LED1, PIN_HIGH);
        }
        else if (state == TOGGLE)
        {
            rt_uint8_t pin_state;
            pin_state = rt_pin_read(PIN_LED1);
            if (pin_state == 1)
            {
                rt_pin_write(PIN_LED1, PIN_LOW);
            }
            else if (pin_state == 0)
            {
                rt_pin_write(PIN_LED1, PIN_HIGH);
            }
        }
        break;

    case LED_2:
        if (state == ON)
        {
            rt_pin_write(PIN_LED2, PIN_LOW);
        }
        else if (state == OFF)
        {
            rt_pin_write(PIN_LED2, PIN_HIGH);
        }
        else if (state == TOGGLE)
        {
            rt_uint8_t pin_state;
            pin_state = rt_pin_read(PIN_LED2);
            if (pin_state == 1)
            {
                rt_pin_write(PIN_LED2, PIN_LOW);
            }
            else if (pin_state == 0)
            {
                rt_pin_write(PIN_LED2, PIN_HIGH);
            }
        }
        break;

    case LED_3:
        if (state == ON)
        {
            rt_pin_write(PIN_LED3, PIN_LOW);
        }
        else if (state == OFF)
        {
            rt_pin_write(PIN_LED3, PIN_HIGH);
        }
        else if (state == TOGGLE)
        {
            rt_uint8_t pin_state;
            pin_state = rt_pin_read(PIN_LED3);
            if (pin_state == 1)
            {
                rt_pin_write(PIN_LED3, PIN_LOW);
            }
            else if (pin_state == 0)
            {
                rt_pin_write(PIN_LED3, PIN_HIGH);
            }
        }
        break;

    case LED_4:
        if (state == ON)
        {
            rt_pin_write(PIN_LED4, PIN_LOW);
        }
        else if (state == OFF)
        {
            rt_pin_write(PIN_LED4, PIN_HIGH);
        }
        else if (state == TOGGLE)
        {
            rt_uint8_t pin_state;
            pin_state = rt_pin_read(PIN_LED4);
            if (pin_state == 1)
            {
                rt_pin_write(PIN_LED4, PIN_LOW);
            }
            else if (pin_state == 0)
            {
                rt_pin_write(PIN_LED4, PIN_HIGH);
            }
        }
        break;

    default:
        break;
    }
}

int user_led_init(void)
{
    /* set LEDs pin mode to output */
    rt_pin_mode(PIN_LED1, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_LED2, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_LED3, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_LED4, PIN_MODE_OUTPUT);
    rt_kprintf("led init.\r\n");
    return RT_EOK;
}
#ifdef FINSH_USING_MSH
INIT_DEVICE_EXPORT(user_led_init);
#endif
