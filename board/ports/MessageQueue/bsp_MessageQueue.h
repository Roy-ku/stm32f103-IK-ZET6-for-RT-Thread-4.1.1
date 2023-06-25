#ifndef __BSP_MESSAGE_QUEUE_H__
#define __BSP_MESSAGE_QUEUE_H__

#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif
#ifdef BSP_USING_MESSAGEQUEUE
#include "MessageQueue.h"
typedef enum
{
	MSG_NONE = 0,

	MSG_Btn2,
	MSG_Btn3,
	MSG_PCF8574_INT,

} BSP_MSG_INFO;

#endif
#ifdef __cplusplus
}
#endif

#endif /* __BSP_MESSAGE_QUEUE_H__ */
