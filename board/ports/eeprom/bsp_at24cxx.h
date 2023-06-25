#ifndef __BSP_AT24CXX_H__
#define __BSP_AT24CXX_H__

#include <board.h>

#ifdef __cplusplus
extern "C"
{
#endif
#ifdef BSP_USING_AT24CXX
#include "at24cxx.h"

#define AT24CXX_ADDR (0xA0 >> 1) // A0 A1 A2 connect GND

    extern at24cxx_device_t at24cxx_dev;

#endif /* BSP_USING_AT24CXX */
#ifdef __cplusplus
}
#endif

#endif /* __BSP_AT24CXX_H__ */
