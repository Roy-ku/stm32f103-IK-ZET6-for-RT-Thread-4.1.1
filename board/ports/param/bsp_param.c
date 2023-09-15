#include <board.h>
#include "bsp_param.h"

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "param"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif

PARAM_T g_tParam;

/* 將16KB 一個磁區的空間預留出來做為參數區 For MDK */
// const uint8_t para_flash_area[16*1024] __attribute__((at(ADDR_FLASH_SECTOR_3)));

/*
*********************************************************************************************************
*	函 數 名: LoadParam
*	功能說明: 從Flash讀參數到g_tParam
*	形    參：無
*	返 回 值: 無
*********************************************************************************************************
*/
void LoadParam(void)
{
#ifdef PARAM_SAVE_TO_FLASH
	/* 讀取CPU Flash中的參數 */
	bsp_ReadCpuFlash(PARAM_ADDR, (uint8_t *)&g_tParam, sizeof(PARAM_T));
#endif

#ifdef PARAM_SAVE_TO_EEPROM
	/* 讀取EEPROM中的參數 */
	at24cxx_read(at24cxx_dev, PARAM_ADDR, (uint8_t *)&g_tParam, sizeof(PARAM_T));
#endif

	/* 填充預設參數 */
	if (g_tParam.ParamVer != PARAM_VER)
	{
		rt_kprintf("The parameter version is not detected, it will initialize it\r\n");
		g_tParam.ParamVer = PARAM_VER;
		g_tParam.BackLight = 255;
		SaveParam(); /* 將新參數寫入Flash */
		rt_kprintf("Initialization complete\r\n");
	}
	else
	{
		rt_kprintf("Param_ver is the latest\r\n");
	}
}

/*
*********************************************************************************************************
*	函 數 名: SaveParam
*	功能說明: 將全域變數g_tParam 寫入到CPU內部Flash
*	形    參: 無
*	返 回 值: 無
*********************************************************************************************************
*/
void SaveParam(void)
{
#ifdef PARAM_SAVE_TO_FLASH
	/* 將全域的參數變數保存到 CPU Flash */
	bsp_WriteCpuFlash(PARAM_ADDR, (unsigned char *)&g_tParam, sizeof(PARAM_T));
#endif

#ifdef PARAM_SAVE_TO_EEPROM
	/* 將全域的參數變數保存到EEPROM */
	at24cxx_write(at24cxx_dev, PARAM_ADDR, (uint8_t *)&g_tParam, sizeof(PARAM_T));
#endif
}

/***************************** (END OF FILE) *********************************/
