#ifndef __BSP_ESP01S_H__
#define __BSP_ESP01S_H__

#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 設定不定長接收 */
#define DATA_CMD_END '\r'  /* 結束位設置為 \r，即回Enter */
#define ONE_DATA_MAXLEN 20 /* 不定長數據的最大長度 */

/* 線程棧相關配置 */
#define ESP01S_THREAD_PRIORITY ((RT_THREAD_PRIORITY_MAX - 1) * 7 / 8)
#define ESP01S_THREAD_STACK_SIZE 256
#define ESP01S_THREAD_TIMESLICE (10U * RT_TICK_PER_SECOND / 1000U) // 10ms
#define ESP01S_WAIT_SEM_MAX_TICK (10U * RT_TICK_PER_SECOND)

#ifdef __cplusplus
}
#endif

#endif /* __BSP_ESP01S_H__ */
