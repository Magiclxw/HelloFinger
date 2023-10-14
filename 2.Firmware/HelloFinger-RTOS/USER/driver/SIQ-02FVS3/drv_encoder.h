#ifndef _DRV_ENCODER_H
#define _DRV_ENCODER_H
#include "sys_config.h"

typedef int(*FUNC_ENCODERKEYRECVTCB)(void);

#define Signal_A_Read	HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)
#define Signal_B_Read	HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)
#define ENCODER_PUSH	HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)

int RegisterEncoderKeyCallBack(FUNC_ENCODERKEYRECVTCB TOUCHRECVCBT);
void ENCODER_Init(void);

#endif
