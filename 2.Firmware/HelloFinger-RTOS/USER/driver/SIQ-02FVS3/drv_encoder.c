#include "drv_encoder.h"
#include "drv_ch9329.h"
#include "app_task_finger.h"
#include "drv_fpm383.h"
#include "app_task_key.h"

__IO uint8_t signal_a = 0;
__IO uint8_t signal_b = 0;

FUNC_ENCODERKEYRECVTCB ENCODERKeyRECVCallback = NULL;

int RegisterEncoderKeyCallBack(FUNC_ENCODERKEYRECVTCB ENCODERRECVCBT)
{
	ENCODERKeyRECVCallback = ENCODERRECVCBT;
	return OPERATE_SUCCESS;
}

void ENCODER_Init(void)
{
	GPIO_InitTypeDef gpio;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	gpio.Mode=GPIO_MODE_IT_RISING_FALLING;
	gpio.Pin=GPIO_PIN_6|GPIO_PIN_7;
	gpio.Pull=GPIO_PULLUP;
	gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&gpio);
	
	gpio.Mode = GPIO_MODE_IT_RISING;	//±àÂëÆ÷°´¼ü
	gpio.Pin = GPIO_PIN_1;
	gpio.Pull = GPIO_PULLDOWN;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn,11,0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	HAL_NVIC_SetPriority(EXTI1_IRQn,11,0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}


