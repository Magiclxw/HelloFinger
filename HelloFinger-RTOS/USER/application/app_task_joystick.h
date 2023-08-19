#ifndef __APP_TASK_JOYSTICK_H
#define __APP_TASK_JOYSTICK_H

#include "sys_config.h"

extern QueueHandle_t Queue_JOYSTICKProcessing_Handle;

#define TASK_JOYSTICK_CONTROL_SIZE	(200)
#define TASK_JOYSTICK_CONTROL_PRIORITY	(8)

#define QUEUE_JOYSTICK_LEN	1
#define QUEUE_JOYSTICK_SIZE	2

int Task_JoyStick_DataCTLCreate(void);
int JoyStick_GiveNotifyFromISR(uint8_t *recData,uint8_t dataSize);
#endif
