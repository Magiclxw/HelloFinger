/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "dma.h"
#include "drv_encoder.h"
#include "drv_ch9329.h"
#include "drv_fpm383.h"
#include "gpio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
extern DMA_HandleTypeDef hdma_spi1_tx;
extern DMA_HandleTypeDef hdma_spi1_rx;
extern DMA_HandleTypeDef hdma_spi2_tx;;
extern TIM_HandleTypeDef rgb_timer_handler;

extern __IO uint8_t signal_a;
extern __IO uint8_t signal_b;
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
//void SVC_Handler(void)
//{
//  /* USER CODE BEGIN SVCall_IRQn 0 */
//////
//  /* USER CODE END SVCall_IRQn 0 */
//  /* USER CODE BEGIN SVCall_IRQn 1 */
//////
//  /* USER CODE END SVCall_IRQn 1 */
//}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
//void PendSV_Handler(void)
//{
//  /* USER CODE BEGIN PendSV_IRQn 0 */
//////
//  /* USER CODE END PendSV_IRQn 0 */
//  /* USER CODE BEGIN PendSV_IRQn 1 */
//////
//  /* USER CODE END PendSV_IRQn 1 */
//}

/**
  * @brief This function handles System tick timer.
  */
//void SysTick_Handler(void)
//{
//  /* USER CODE BEGIN SysTick_IRQn 0 */
//////
//  /* USER CODE END SysTick_IRQn 0 */
//  HAL_IncTick();
//  /* USER CODE BEGIN SysTick_IRQn 1 */
//////
//  /* USER CODE END SysTick_IRQn 1 */
//}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */
extern FUNC_USARTRECVTCB USART1RECVCallback;
extern FUNC_USARTRECVTCB USART2RECVCallback;
extern FUNC_TOUCHRECVTCB TOUCHRECVCallback;
extern FUNC_ENCODERKEYRECVTCB ENCODERKeyRECVCallback;
extern FUNC_ACTIONKEYRECVTCB ActionKeyRECVCallback;
extern FUNC_NORMALKEYRECVTCB	NormalKeyRECVCallback;

extern DMA_HandleTypeDef hdma_adc1;

void USART1_IRQHandler(void)	//ch9329
{
	uint8_t recByte = 0;
	HAL_UART_IRQHandler(&huart1);
	HAL_UART_Receive(&huart1,&recByte,1,0);
	if(USART1RECVCallback != NULL)
	{
		USART1RECVCallback(&recByte,1);
	}
	huart1.Instance->CR1 |= USART_CR1_RXNEIE;
}

void USART2_IRQHandler(void)	//FPM383C
{
	uint8_t recByte = 0;
	HAL_UART_IRQHandler(&huart2);
	HAL_UART_Receive(&huart2,&recByte,1,0);
	if(USART2RECVCallback != NULL)
	{
		USART2RECVCallback(&recByte,1);
	}
	huart2.Instance->CR1 |= USART_CR1_RXNEIE;
}


void EXTI1_IRQHandler(void)	//编码器按键中断
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

void EXTI3_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

void EXTI4_IRQHandler(void)	//手指触摸信号
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void EXTI9_5_IRQHandler(void)		
{
	uint32_t status = EXTI->PR;
	if(status & 0x40){	//编码器信号中断
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
		EXTI->PR &= ~0x40;
	}
	if(status & 0x80){	//编码器信号中断
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);		//调用中断处理公用函数
		EXTI->PR &= ~0x80;
	}
	if(status & 0x100){	//按键中断
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
		EXTI->PR &= ~0x100;
	} 
}

void EXTI15_10_IRQHandler(void)
{
	uint32_t status = EXTI->PR;
	if(status & (1<<11))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
		EXTI->PR &= ~(1<<11);
	}
	if(status & (1<<14))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
		EXTI->PR &= ~(1<<14);
	}
}

void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}
void DMA1_Channel2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel2_IRQn 0 */

  /* USER CODE END DMA1_Channel2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi1_rx);
  /* USER CODE BEGIN DMA1_Channel2_IRQn 1 */

  /* USER CODE END DMA1_Channel2_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel3 global interrupt.
  */
void DMA1_Channel3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel3_IRQn 0 */

  /* USER CODE END DMA1_Channel3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi1_tx);
  /* USER CODE BEGIN DMA1_Channel3_IRQn 1 */

  /* USER CODE END DMA1_Channel3_IRQn 1 */
}

void DMA1_Channel5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel5_IRQn 0 */

  /* USER CODE END DMA1_Channel5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi2_tx);
  /* USER CODE BEGIN DMA1_Channel5_IRQn 1 */

  /* USER CODE END DMA1_Channel5_IRQn 1 */
}

void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&rgb_timer_handler);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin){
		case GPIO_PIN_1:	//编码器按键按下
		{
			//CH9329_REL_Mouse_Ctrl(0,0,0,button_RIGHT);
			//Delay_ms(20);
			//CH9329_REL_Mouse_Ctrl(0,0,0,button_NULL);
			//Con_Sleep();
			if(ENCODERKeyRECVCallback != NULL)
			{
				ENCODERKeyRECVCallback();
			}
			break;
		}
		
		case GPIO_PIN_3:
		{
			CH9329_REL_Mouse_Ctrl(0,0,0,button_RIGHT);
			delay_ms(20);
			CH9329_REL_Mouse_Ctrl(0,0,0,button_NULL);
			break;
		}
		
		case GPIO_PIN_4:
		{
			if(TOUCHRECVCallback != NULL)
			{
				TOUCHRECVCallback();
			}
			break;
		}
		
		case GPIO_PIN_6:
		{
			if(Signal_A_Read == GPIO_PIN_SET && Signal_B_Read == GPIO_PIN_RESET && signal_a == 0){
				signal_a = 1;
			}else if(Signal_A_Read == GPIO_PIN_RESET && Signal_B_Read == GPIO_PIN_SET && signal_a == 1){
				CH9329_REL_Mouse_Ctrl(0x01,0,0,button_NULL);
				signal_a = 0;
			}else{
				signal_a = 0;
			}
			break;
		}
			
		case GPIO_PIN_7:
		{
			if(Signal_B_Read == GPIO_PIN_SET && Signal_A_Read == GPIO_PIN_RESET && signal_b == 0){
				signal_b = 1;
			}else if(Signal_B_Read == GPIO_PIN_RESET && Signal_A_Read == GPIO_PIN_SET && signal_b == 1){
				CH9329_REL_Mouse_Ctrl(0xFF,0,0,button_NULL);
				signal_b = 0;
			}else{
				signal_b = 0;
			}
			break;
		}
		case GPIO_PIN_8:
		{
			if(NormalKeyRECVCallback != NULL)
			{
				NormalKeyRECVCallback();
			}
			break;
		}
		case GPIO_PIN_11:
		{
			if(NormalKeyRECVCallback != NULL)
			{
				NormalKeyRECVCallback();
			}
			break;
		}
		case GPIO_PIN_14:
		{
			if(ActionKeyRECVCallback != NULL)
			{
				ActionKeyRECVCallback();
			}
		}
		
		
		
		
	}
}
/* USER CODE END 1 */
