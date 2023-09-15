/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "cpu_flash"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif

#include "bsp_cpu_flash.h"
#include "drv_flash.h"

#ifdef BSP_CHIP_FLASH_TEST_SAMPLE
/**
 * @brief 測試內部Flash讀寫
 */
void bsp_CpuFlash_Test(void)
{
	uint32_t IFLASH_TEST = 0x0807F800;
	rt_uint8_t ucTest[2] = {0x33, 0xAA};
	rt_uint8_t ucTest_read[2] = {0};
	LOG_D("bsp_EraseCpuFlash %d", stm32_flash_erase(IFLASH_TEST,2));
	LOG_D("bsp_WriteCpuFlash %d", stm32_flash_write((uint32_t)IFLASH_TEST, ucTest, 2));
	stm32_flash_read(IFLASH_TEST, ucTest_read, 2);
	LOG_D("Read data: ucTest_read[0] = %x,ucTest_read[1] = %x", ucTest_read[0], ucTest_read[1]);
}
#endif

/***************************** (END OF FILE) *********************************/
