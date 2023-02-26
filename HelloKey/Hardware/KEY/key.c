#include "key.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef gpio;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	gpio.Mode=GPIO_MODE_INPUT;
	gpio.Pin=GPIO_PIN_10|GPIO_PIN_11;
	gpio.Pull=GPIO_PULLUP;
	gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&gpio);
	
}