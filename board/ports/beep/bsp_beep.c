#include <rtthread.h>
#include <stdint.h>
#include <rtdevice.h>
#include <board.h>

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "bsp_beep"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif
/****************************************************************************************/
/* defined the BEEP pin: PG7 */
#define PIN_BEEP GET_PIN(G, 7)
/****************************************************************************************/
static int bsp_beep_init(void);
/****************************************************************************************/
static int bsp_beep_init(void)
{
	beep_init(PIN_BEEP, PIN_LOW);
  rt_kprintf("beep init.\r\n");
  return RT_EOK;
}
#ifdef FINSH_USING_MSH
INIT_DEVICE_EXPORT(bsp_beep_init);
#endif
