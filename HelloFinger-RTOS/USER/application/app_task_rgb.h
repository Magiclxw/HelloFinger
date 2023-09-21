#ifndef __APP_TASK_RGB_H
#define __APP_TASK_RGB_H

#include "sys_config.h"
#include "..\USER\driver\WS2812\drv_ws2812b.h"

#define TASK_RGB_PROCESS_SIZE	(200)
#define TASK_RGB_PROCESS_PRIORITY	(7)

#define QUEUE_RGB_PROCESS_LEN	(1)
#define QUEUE_RGB_PROCESS_SIZE (4)

#define EVENT_RGB_TRANS_OVER	0x01

int Task_RGB_ProcessCreate(void);


#endif
