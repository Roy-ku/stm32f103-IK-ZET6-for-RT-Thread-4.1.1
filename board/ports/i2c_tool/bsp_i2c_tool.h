#ifndef __BSP_I2C_TOOL_H__
#define __BSP_I2C_TOOL_H__

#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif
rt_size_t i2c_device_check(struct rt_i2c_bus_device *bus,char addr);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_I2C_TOOL_H__ */
