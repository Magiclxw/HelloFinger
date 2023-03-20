#include "key.h"
#include "delay.h"
#include "ch9329.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef gpio;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	gpio.Mode=GPIO_MODE_IT_FALLING;
	gpio.Pin=GPIO_PIN_8|GPIO_PIN_11;
	gpio.Pull=GPIO_PULLUP;
	gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,0);       //抢占优先级为2，子优先级为0
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,1);       //抢占优先级为2，子优先级为0
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	Delay_ms(10);
	switch (GPIO_Pin){
		case GPIO_PIN_8:
			while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)){
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
			}
			SET_EN;
			CH9329_WorkMode_Config(WORKMODE_SOFT_0);
			CH9329_SerialMode_Config(SERIALMODE_SOFT_0);
			CH9329_Set_Cfg();
			SET_DEN;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
			break;
		case GPIO_PIN_11:
			while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)){
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);
			}
			SET_EN;
			CH9329_WorkMode_Config(WORKMODE_SOFT_3);
			CH9329_SerialMode_Config(SERIALMODE_SOFT_2);
			CH9329_Set_Cfg();
			SET_DEN;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);
			break;
	}
}
