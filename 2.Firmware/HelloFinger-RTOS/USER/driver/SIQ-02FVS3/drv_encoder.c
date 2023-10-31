#include "drv_encoder.h"
#include "drv_ch9329.h"
#include "gpio.h"


__IO uint8_t signal_a = 0;
__IO uint8_t signal_b = 0;

FUNC_ENCODERKEYRECVTCB ENCODERKeyRECVCallback = NULL;	//编码器按键回调函数
FUNC_ENCODERRECVTCB	ENCODERRECVCallback = NULL;	//编码器触发回调函数

int RegisterEncoderKeyCallBack(FUNC_ENCODERKEYRECVTCB ENCODERRECVCBT)
{
	ENCODERKeyRECVCallback = ENCODERRECVCBT;
	return OPERATE_SUCCESS;
}

int RegisterEncoderCallBack(FUNC_ENCODERRECVTCB ENCODERRECVCBT)
{
	ENCODERRECVCallback = ENCODERRECVCBT;
	return OPERATE_SUCCESS;
}

int ENCODER_Init(void)
{
	GPIO_InitTypeDef gpio;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	gpio.Mode=GPIO_MODE_IT_RISING_FALLING;
	gpio.Pin=MCU_GPIO_ENCODER_SIGNAL_A|MCU_GPIO_ENCODER_SIGNAL_B;
	gpio.Pull=GPIO_PULLUP;
	gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&gpio);
	
	gpio.Mode = GPIO_MODE_IT_RISING;	//编码器按键
	gpio.Pin = MCU_GPIO_ENCODER_KEY_PIN;
	gpio.Pull = GPIO_PULLDOWN;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn,11,0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	HAL_NVIC_SetPriority(EXTI1_IRQn,11,0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	
	return OPERATE_SUCCESS;
}


