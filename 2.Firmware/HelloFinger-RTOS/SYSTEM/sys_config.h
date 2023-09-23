#ifndef __SYS_CONFIG_H
#define __SYS_CONFIG_H
#include "stm32f1xx.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "delay.h"
#include "usart.h"
#include "semphr.h"
#include "event_groups.h"
#include "adc.h"
#include "dma.h"
#include "crc.h"

#define OPERATE_SUCCESS 													(0)
#define OPERATE_ERROR_INVALID_PARAMETERS 					(-1)
#define OPERATE_ERROR_UNSUPPORTED 								(-2)
#define OPERATE_ERROR_EXCEPTION 									(-3)
#define OPERATE_ERROR_BUSY 												(-4)
#define OPERATE_ERROR_CREATEFAILED 								(-5)
#define OPERATE_ERROR_OPENFAILED 									(-6)
#define OPERATE_ERROR_TIMEOUT 										(-7)
#define OPERATE_ERROR_BUFFNOTENOUGH 							(-8) 

#define EVENT_INDEX_LIST		0x00001
#define EVENT_AUTO_ENROLL		0x00002
#define EVENT_DELETE_CHAR		0x00004
#define EVENT_TOUCH_DETECT	0x00008

extern EventGroupHandle_t FingerEvent_Handle;


typedef enum DATA_RECV_STATE
{
	DATA_RECV_STATE_NO_GET,
	DATA_RECV_STATE_GET
}DATA_RECV_STATE_e;

#endif
