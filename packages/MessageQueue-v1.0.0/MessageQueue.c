/**
 * @file MessageQueue.c
 * @brief MessageQueue
 * @author Roy (xu3jo3m4@gmail.com)
 * @version 1.0
 * @date 2023-06-03
 * @par 修改日誌
 *      2023-06-03 ----- 初版
 *
 * @copyright Copyright (c) 2023  XXXX公司
 */

#include <rtdevice.h>
#include <rtthread.h>
#include "MessageQueue.h"
/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "MQ"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif

#ifdef PKG_USING_MESSAGEQUEUE

struct rt_semaphore MQ_sem;

MSG_FIFO_T g_tMsg;

/**
 * @brief 初始化消息緩衝區
 */
int MQ_InitMsg(void)
{
	rt_err_t result = RT_EOK;
	g_tMsg.Read = g_tMsg.Write;
	result = rt_sem_init(&MQ_sem, "MQ_sem", 0, RT_IPC_FLAG_FIFO);
	if (result != RT_EOK)
	{
		rt_kprintf("init static semaphore failed.\r\n");
	}
	else
	{
		rt_kprintf("MessageQueue init.\r\n");
	}
	return 0;
}

/**
 * @brief 輸出目前Msg緩衝區的值
 */
void MQ_PrintMsgBuffer(void)
{
	uint8_t i;
	if (g_tMsg.Read != g_tMsg.Write)
	{
		for (i = g_tMsg.Read; i != g_tMsg.Write; i = (i + 1) % MSG_FIFO_SIZE)
		{
			MSG_T *p = &g_tMsg.Buf[i];
			LOG_D("MsgCode: %d, MsgParam: %d", p->MsgCode, p->MsgParam);
		}
	}
	else
	{
		LOG_D("The container is empty.");
	}
	LOG_D("-----------");
}

/**
 * @brief 將一個消息押入消息FIFO緩衝區
 * @param _MsgCode 消息Code
 * @param _MsgParam 消息參數，一般向某個特定的結構體，或是0
 */
void MQ_PutMsg(uint16_t _MsgCode, uint32_t _MsgParam)
{
	rt_err_t result = RT_EOK;
	if (g_tMsg.Read == (g_tMsg.Write + 1) % MSG_FIFO_SIZE)
	{
		// 緩衝區已滿，無法插入新的消息
		LOG_D("The container is full and cannot insert new elements.\n");
		return;
	}

	g_tMsg.Buf[g_tMsg.Write].MsgCode = _MsgCode;
	g_tMsg.Buf[g_tMsg.Write].MsgParam = _MsgParam;

	if (++g_tMsg.Write >= MSG_FIFO_SIZE)
	{
		g_tMsg.Write = 0;
	}
	result = rt_sem_release(&MQ_sem);
	if (RT_EOK == result)
		LOG_D("semaphore release ok.");
	else
		LOG_D("semaphore release failed.");
}

/**
 * @brief 將一個消息押入消息FIFO緩衝區首位
 * @param _MsgCode 消息Code
 * @param _MsgParam 消息參數，一般向某個特定的結構體，或是0
 */
void MQ_PutMsgUrgent(uint16_t _MsgCode, uint32_t _MsgParam)
{
	rt_err_t result = RT_EOK;
	if (g_tMsg.Read == (g_tMsg.Write + 1) % MSG_FIFO_SIZE)
	{
		// 緩衝區已滿，無法插入新的消息
		LOG_D("The container is full and cannot insert new elements.");
		return;
	}

	if (g_tMsg.Read == 0)
	{
		g_tMsg.Read = MSG_FIFO_SIZE - 1;
	}
	else
	{
		g_tMsg.Read--;
	}

	g_tMsg.Buf[g_tMsg.Read].MsgCode = _MsgCode;
	g_tMsg.Buf[g_tMsg.Read].MsgParam = _MsgParam;

	result = rt_sem_release(&MQ_sem);
	if (RT_EOK == result)
		LOG_D("semaphore release ok.");
	else
		LOG_D("semaphore release failed.");
}

/**
 * @brief 從消息FIFO緩衝區讀取一個鍵值
 * @param _pMsg 消息Code
 * @return uint8_t 0 表示無消息； 1表示有消息
 */
uint8_t MQ_GetMsg(MSG_T *_pMsg)
{
	MSG_T *p;
	rt_err_t result = RT_EOK;

	/* wait the semaphore forever */
	result = rt_sem_take(&MQ_sem, RT_WAITING_FOREVER);
	if (result != RT_EOK)
	{
		LOG_D("take a static semaphore, failed.");
	}

	if (g_tMsg.Read == g_tMsg.Write)
	{
		return 0;
	}
	else
	{
		p = &g_tMsg.Buf[g_tMsg.Read];

		if (++g_tMsg.Read >= MSG_FIFO_SIZE)
		{
			g_tMsg.Read = 0;
		}

		_pMsg->MsgCode = p->MsgCode;
		_pMsg->MsgParam = p->MsgParam;
		return 1;
	}
}

/**
 * @brief 從消息FIFO緩衝區讀取一個鍵值。使用第二個讀取指針。可以2個進程同時訪問消息區
 * @param _pMsg 消息Code
 * @return uint8_t 0 表示無消息； 1表示有消息
 */
uint8_t MQ_GetMsg2(MSG_T *_pMsg)
{
	MSG_T *p;
	rt_err_t result = RT_EOK;

	/* wait the semaphore forever */
	result = rt_sem_take(&MQ_sem, RT_WAITING_FOREVER);
	if (result != RT_EOK)
	{
		LOG_D("take a static semaphore, failed.");
	}

	if (g_tMsg.Read2 == g_tMsg.Write)
	{
		return 0;
	}
	else
	{
		p = &g_tMsg.Buf[g_tMsg.Read2];

		if (++g_tMsg.Read2 >= MSG_FIFO_SIZE)
		{
			g_tMsg.Read2 = 0;
		}

		_pMsg->MsgCode = p->MsgCode;
		_pMsg->MsgParam = p->MsgParam;
		return 1;
	}
}

/**
 * @brief 清空消息FIFO緩衝區
 */
void MQ_ClearMsg(void)
{
	rt_err_t result = RT_EOK;
	g_tMsg.Read = g_tMsg.Write;

	result = rt_sem_detach(&MQ_sem);
	if (result != RT_EOK)
	{
		result = rt_sem_init(&MQ_sem, "MQ_sem", 0, RT_IPC_FLAG_FIFO);
		if (result != RT_EOK)
		{
			rt_kprintf("init static semaphore failed.\r\n");
		}
		else
		{
			rt_kprintf("MessageQueue init.\r\n");
		}
	}
}
#endif /* PKG_USING_MESSAGEQUEUE */

#if defined(FINSH_USING_MSH) && defined(PKG_USING_MESSAGEQUEUE)
INIT_APP_EXPORT(MQ_InitMsg);
#endif /* FINSH_USING_MSH */
/***************************** (END OF FILE) *********************************/
