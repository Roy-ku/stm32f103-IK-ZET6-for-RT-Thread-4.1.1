#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    LED_1 = 1,
    LED_2,
    LED_3,
    LED_4,
} user_led_t;

typedef enum
{
    ON = 1,
    OFF,
    TOGGLE,

} user_led_state_t;
int user_led_init(void);
void led_config(user_led_t led, user_led_state_t state);
#ifdef __cplusplus
}
#endif

#endif /* __BSP_LED_H__ */
