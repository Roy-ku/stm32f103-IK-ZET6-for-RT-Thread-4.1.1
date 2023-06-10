#include <rtthread.h>
#include <stdint.h>
#include <rtdevice.h>
#include <board.h>

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "drv_beep"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif
/****************************************************************************************/
/* defined the BEEP pin: PG7 */
#define PIN_BEEP GET_PIN(G, 7)
/****************************************************************************************/
static int user_beep_init(void);
/****************************************************************************************/
static int user_beep_init(void)
{
	beep_init(PIN_BEEP, PIN_LOW);
  LOG_D("beep init.");
  return 0;
}
#ifdef FINSH_USING_MSH
INIT_DEVICE_EXPORT(user_beep_init);
#endif
