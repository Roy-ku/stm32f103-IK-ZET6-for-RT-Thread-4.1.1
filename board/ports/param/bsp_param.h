#ifndef __PARAM_H
#define __PARAM_H

/* 下面2行宏只能選擇其一 */
#define PARAM_SAVE_TO_EEPROM /* 參數存儲到外部的EEPROM (AT24C128) */
//#define PARAM_SAVE_TO_FLASH		/* 參數存儲到CPU內部Flash */

#ifdef PARAM_SAVE_TO_EEPROM
#define PARAM_ADDR 0 /* 參數區地址 */
#endif

#ifdef PARAM_SAVE_TO_FLASH
#define PARAM_ADDR ADDR_FLASH_SECTOR_3 /* 0x0800C000 中間的16KB磁區用來存放參數 */
									   //#define PARAM_ADDR	 ADDR_FLASH_SECTOR_11		/* 0x080E0000 Flash最後128K磁區用來存放參數 */
#endif

#define PARAM_VER 0x00000001 /* 參數版本 */

/* 全域參數 */
typedef struct
{
	uint32_t ParamVer; /* 參數區版本控制（可用于程式升級時，決定是否對參數區進行升級） */
	uint8_t BackLight; /* LCD背光亮度 */
} PARAM_T;

extern PARAM_T g_tParam;

void LoadParam(void);
void SaveParam(void);

#endif
