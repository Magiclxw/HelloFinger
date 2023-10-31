#ifndef _DRV_ENCODER_H
#define _DRV_ENCODER_H
#include "sys_config.h"

typedef int(*FUNC_ENCODERKEYRECVTCB)(void);
typedef int(*FUNC_ENCODERRECVTCB)(uint32_t);

#define Signal_A_Read	HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)
#define Signal_B_Read	HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)
#define ENCODER_PUSH	HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)

int RegisterEncoderKeyCallBack(FUNC_ENCODERKEYRECVTCB ENCODERRECVCBT);
int RegisterEncoderCallBack(FUNC_ENCODERRECVTCB ENCODERRECVCBT);
int ENCODER_Init(void);

#endif
