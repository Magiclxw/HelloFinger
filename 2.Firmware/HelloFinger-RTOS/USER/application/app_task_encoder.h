#ifndef __APP_TASK_ENCODER_H
#define __APP_TASK_ENCODER_H
#include "sys_config.h"

#define TASK_ENCODER_CONTROL_SIZE 100
#define TASK_ENCODER_CONTROL_PRIORITY 13

int ENCODER_NotifyFromISR(uint32_t dir);
int Task_Encoder_CTLCreate(void);

#endif
