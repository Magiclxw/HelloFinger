#ifndef __DRV_JOYSTICK_H
#define __DRV_JOYSTICK_H

#include "sys_config.h"

typedef int(*FUNC_ADCRECVTCB)(uint8_t *pData, uint8_t Datasize);

extern ADC_HandleTypeDef hadc1;

extern uint16_t value_X_Y[2];

#define MIN_OFFSET 36
#define MAX_OFFSET 44

/* 默认看门狗临界值 */
#define DEFAULT_HIGH_THRESHOLD	2200
#define DEFAULT_LOW_THRESHOLD		1900

void MX_ADC1_Init(void);
int RegisterADC1ReceiveCallBack(FUNC_USARTRECVTCB ADC1READYVCBT);



#endif


