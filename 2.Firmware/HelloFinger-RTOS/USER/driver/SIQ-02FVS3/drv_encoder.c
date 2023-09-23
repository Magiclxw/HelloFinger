#include "drv_encoder.h"
#include "drv_ch9329.h"
#include "app_task_finger.h"
#include "drv_fpm383.h"
#include "app_task_key.h"

__IO uint8_t signal_a = 0;
__IO uint8_t signal_b = 0;


void ENCODER_Init(void)
{
	GPIO_InitTypeDef gpio;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	gpio.Mode=GPIO_MODE_IT_RISING_FALLING;
	gpio.Pin=GPIO_PIN_8|GPIO_PIN_9;
	gpio.Pull=GPIO_PULLUP;
	gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&gpio);
	
	gpio.Mode = GPIO_MODE_IT_RISING;	//编码器按键
	gpio.Pin = GPIO_PIN_1;
	gpio.Pull = GPIO_PULLDOWN;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn,1,0);       //抢占优先级为2，子优先级为0
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	HAL_NVIC_SetPriority(EXTI1_IRQn,1,0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin){
		case GPIO_PIN_8:
		{
			if(Signal_A_Read == GPIO_PIN_SET && Signal_B_Read == GPIO_PIN_RESET && signal_a == 0){
				signal_a = 1;
			}else if(Signal_A_Read == GPIO_PIN_RESET && Signal_B_Read == GPIO_PIN_SET && signal_a == 1){
				REL_Mouse_Ctrl(0x01,0,0,button_NULL);
				signal_a = 0;
			}else{
				signal_a = 0;
			}
			break;
		}
			
		case GPIO_PIN_9:
		{
			if(Signal_B_Read == GPIO_PIN_SET && Signal_A_Read == GPIO_PIN_RESET && signal_b == 0){
				signal_b = 1;
			}else if(Signal_B_Read == GPIO_PIN_RESET && Signal_A_Read == GPIO_PIN_SET && signal_b == 1){
				REL_Mouse_Ctrl(0xFF,0,0,button_NULL);
				signal_b = 0;
			}else{
				signal_b = 0;
			}
			break;
		}
		
		case GPIO_PIN_1:
		{
			REL_Mouse_Ctrl(0,0,0,button_RIGHT);
			//Delay_ms(20);
			//REL_Mouse_Ctrl(0,0,0,button_NULL);
			//Con_Sleep();
			break;
		}
		
		case GPIO_PIN_4:
		{
			//g_finger_rec_flag = 1;
			Generate_AutoIdentify(0x03,0xFFFF,0x0007);
			HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_autoidentify,g_autoidentify.LEN[0]<<8|g_autoidentify.LEN[1]+FIXED_CMD_LEN,1000);
			portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
			if(FingerEvent_Handle != NULL)
			{
				
				xEventGroupSetBitsFromISR((EventGroupHandle_t)FingerEvent_Handle,(EventBits_t)EVENT_TOUCH_DETECT,&xHigherPriorityTaskWoken);
				portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			}
			
		}
		
		break;
	}
}


