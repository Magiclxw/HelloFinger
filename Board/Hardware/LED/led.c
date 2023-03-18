#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef gpio;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14|GPIO_PIN_15,GPIO_PIN_RESET);
	
	gpio.Mode=GPIO_MODE_OUTPUT_PP;
	gpio.Pin=GPIO_PIN_14|GPIO_PIN_15;
	gpio.Pull=GPIO_PULLDOWN;
	gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&gpio);
}
