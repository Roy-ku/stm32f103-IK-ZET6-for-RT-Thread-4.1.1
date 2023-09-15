#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "bsp_timer"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif

static struct rt_timer bsp_timer_2S = {0};

static void timer_2000ms_callback(void *param)
{
    //MQ_PutMsg(MSG_AHT10_UPDATE, 0);
}

static int bsp_timer_init(void)
{
    rt_timer_init(&bsp_timer_2S, "bsp_timer_2S", timer_2000ms_callback, RT_NULL, 2000,
                  RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);

    rt_timer_start(&bsp_timer_2S);
    return RT_EOK;
}
#ifdef FINSH_USING_MSH
INIT_DEVICE_EXPORT(bsp_timer_init);
#endif /* FINSH_USING_MSH */
