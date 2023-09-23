#ifndef __ADC_H
#define __ADC_H
#include "sys_config.h"

extern ADC_HandleTypeDef hadc1;

extern uint16_t value_X_Y[2];

#define MIN_OFFSET 36
#define MAX_OFFSET 44

void MX_ADC1_Init(void);
int RegisterADC1ReceiveCallBack(FUNC_USARTRECVTCB ADC1READYVCBT);

#endif
