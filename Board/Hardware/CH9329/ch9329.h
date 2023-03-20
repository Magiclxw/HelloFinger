#ifndef __CH9329_H
#define __CH9329_H
#include "stm32f1xx.h"

/* 配置前后需要一定延时 */
#define SET_EN	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET)	//CH9329芯片参数配置引脚使能
#define SET_DEN	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET)	//CH9329芯片参数配置引脚禁止

#define WORKMODE_SOFT_0		0x00
#define WORKMODE_SOFT_1		0x01
#define WORKMODE_SOFT_2		0x02
#define WORKMODE_SOFT_3		0x03
#define WORKMODE_HARD_0		0x80
#define WORKMODE_HARD_1		0x81
#define WORKMODE_HARD_2		0x82
#define WORKMODE_HARD_3		0x83

#define SERIALMODE_SOFT_0				0x00
#define SERIALMODE_SOFT_1				0x01
#define SERIALMODE_SOFT_2				0x02
#define SERIALMODE_HARD_0				0x80
#define SERIALMODE_HARD_1				0x81
#define SERIALMODE_HARD_2				0x82

#define AUTOENTERFLAG_ENABLE		0x01
#define AUTOENTERFLAG_DISABLE		0x00

extern uint8_t CH9329_CONFIG[50];

void CH9329_WorkMode_Config(uint8_t workmode);
void CH9329_SerialMode_Config(uint8_t serialmode);
void CH9329_SerialAddr_Config(uint8_t addr);
void CH9329_SerialBaudRate_Config(uint8_t* baudrate);
void CH9329_SerialInterval_Config(uint8_t* interval);
void CH9329_Vid_Pid_Config(uint16_t vid,uint16_t pid);
void CH9329_Get_Cfg(void);
void CH9329_Set_Cfg(void);
void CH9329_Init(void);
void CH9329_Reset(void);


#endif
