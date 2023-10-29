/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "sys_config.h"
/* USER CODE BEGIN 0 */
FUNC_ACTIONKEYRECVTCB ActionKeyRECVCallback = NULL;
FUNC_NORMALKEYRECVTCB	NormalKeyRECVCallback = NULL;
FUNC_JOYCONKEYRECVTCB JoyconKeyRECVCallback = NULL;

int RegisterActionKeyCallBack(FUNC_ACTIONKEYRECVTCB ACTIONRECVCBT)
{
	ActionKeyRECVCallback = ACTIONRECVCBT;
	return OPERATE_SUCCESS;
}

int RegisterNormalKeyCallBack(FUNC_NORMALKEYRECVTCB NORMALKEYRECVCBT)
{
	NormalKeyRECVCallback = NORMALKEYRECVCBT;
	return OPERATE_SUCCESS;
}

int RegisterJoyconKeyCallBack(FUNC_JOYCONKEYRECVTCB JOYCONKEYRECVCBT)
{
	JoyconKeyRECVCallback = JOYCONKEYRECVCBT;
	return OPERATE_SUCCESS;
}
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef gpio;
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	gpio.Pin = MCU_GPIO_KEY0_PIN|MCU_GPIO_KEY1_PIN;
	gpio.Mode = GPIO_MODE_IT_RISING_FALLING;
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio);
	
	gpio.Pin = MCU_GPIO_JOYCON_KEY_PIN;
	gpio.Mode = GPIO_MODE_IT_RISING;
	gpio.Pull = GPIO_PULLDOWN;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio);
	
	gpio.Pin = MCU_GPIO_KEY3_PIN;
	gpio.Mode = GPIO_MODE_INPUT;
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOB,&gpio);
	
	gpio.Pin = MCU_GPIO_KEY2_PIN;
	gpio.Mode = GPIO_MODE_IT_FALLING;
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOB,&gpio);
	
	HAL_NVIC_SetPriority(EXTI0_IRQn,12,0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	
	HAL_NVIC_SetPriority(EXTI9_5_IRQn,11,0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	HAL_NVIC_SetPriority(EXTI15_10_IRQn,9,0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
