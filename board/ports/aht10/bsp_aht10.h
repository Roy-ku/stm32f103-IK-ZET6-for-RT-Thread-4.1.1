#ifndef __BSP_AHT10_H__
#define __BSP_AHT10_H__

#include <board.h>

#ifdef __cplusplus
extern "C"
{
#endif
#ifdef BSP_USING_AHT10
#include "aht10.h"

#define AHT10_ADDR (0x70 >> 1) // 0x38
    extern aht10_device_t aht10_dev;

#endif /* BSP_USING_AHT10 */
#ifdef __cplusplus
}
#endif

#endif /* __BSP_AHT10_H__ */
