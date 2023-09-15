#ifndef _BSP_CPU_FLASH_H_
#define _BSP_CPU_FLASH_H_

#include <board.h>
#ifdef BSP_CHIP_FLASH_TEST_SAMPLE
#define CPU_FLASH_BASE_ADDR STM32_FLASH_START_ADRESS /* APP開始地址 */
#define CPU_FLASH_END_ADDR STM32_FLASH_END_ADDRESS   /* FLASH結束地址 */

#define CPU_FLASH_SIZE STM32_FLASH_SIZE  /* FLASH總容量 單位:Byte */
#define CPU_FLASH_SECTOR_SIZE (2 * 1024) /* 頁區大小，單位:Byte */
void bsp_CpuFlash_Test(void);
#endif
#endif

/***************************** (END OF FILE) *********************************/
