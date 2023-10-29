/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
typedef int(*FUNC_ACTIONKEYRECVTCB)(void);
typedef int(*FUNC_NORMALKEYRECVTCB)(void);
typedef int(*FUNC_JOYCONKEYRECVTCB)(void);
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

//GPIOA
#define MCU_GPIO_JOYCON_KEY_PIN	GPIO_PIN_0
#define MCU_GPIO_KEY0_PIN	GPIO_PIN_11
#define MCU_GPIO_KEY1_PIN	GPIO_PIN_8
//GPIOB
#define MCU_GPIO_KEY2_PIN	GPIO_PIN_14
#define MCU_GPIO_KEY3_PIN	GPIO_PIN_13

//GPIOC



/* USER CODE END Private defines */

void MX_GPIO_Init(void);
int RegisterActionKeyCallBack(FUNC_ACTIONKEYRECVTCB ACTIONRECVCBT);
int RegisterNormalKeyCallBack(FUNC_NORMALKEYRECVTCB NORMALKEYRECVCBT);
int RegisterJoyconKeyCallBack(FUNC_JOYCONKEYRECVTCB JOYCONKEYRECVCBT);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

