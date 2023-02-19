#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef gpio;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	gpio.Mode=GPIO_MODE_OUTPUT_PP;
	gpio.Pin=GPIO_PIN_13;
	gpio.Pull=GPIO_PULLDOWN;
	gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC,&gpio);
	
	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
	//gpio.Mode=GPIO_MODE_OUTPUT_PP;
	//gpio.Pin=GPIO_PIN_12;
	//gpio.Pull=GPIO_PULLDOWN;
	//gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	//HAL_GPIO_Init(GPIOA,&gpio);
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
}
