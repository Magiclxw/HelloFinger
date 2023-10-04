#ifndef __APP_TASK_RGB_H
#define __APP_TASK_RGB_H

#include "sys_config.h"
#include "..\USER\driver\WS2812\drv_ws2812b.h"

#define TASK_RGB_PROCESS_SIZE	(200)
#define TASK_RGB_PROCESS_PRIORITY	(7)

#define QUEUE_RGB_PROCESS_LEN	(1)
#define QUEUE_RGB_PROCESS_SIZE (4)

#define EVENT_RGB_TRANS_OVER	0x01

typedef enum RESULT_
{
	RESULT_SUCCESS,
	RESULT_FAILED,
}RESULT_e;

int Task_RGB_ProcessCreate(void);
void RGB_Effect(uint8_t r,uint8_t g,uint8_t b,uint16_t delay,uint8_t times);
void Display_Result(uint8_t result);
#endif
