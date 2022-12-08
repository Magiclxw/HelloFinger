/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led.h"
#include "delay.h"
#include "ZW800.h"
#include "func.h"
#include "kmfunc.h"
#include "message.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern uint16_t USART1_RX_STA;
extern uint16_t USART2_RX_STA;
extern uint8_t RxData1[100];


extern __IO uint8_t rxstate;
uint8_t data[10];
extern uint8_t LEN;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t test[5]="test";
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	LED_Init();
	Delay_Init();
	CmdConnect();
	
	//HAL_NVIC_DisableIRQ(USART1_IRQn);
	uint8_t ID[2]={0x00,0x04};
	uint8_t PARAM[2]={0x00,0x00};
	//Con_AutoEnroll(ID,4,PARAM);
	//uint8_t PassWord[4]={0x00,0x00,0x00,0x00};
	//uint8_t *tmp=CMD_ControlBLN(2,4,2);
	//HAL_UART_Transmit(&huart1,tmp,ControlBLNSize,1000);
	
	//Con_GetDummyTempleteNo();
	//UnLock(960,625);
	//GetTableState();
	Con_Register(1,7);
	
//------------------------------指纹模块状态获取与初始化-----------------------------------/
	
	//if(!Con_HandShake())						//握手
	//{
	//	HAL_UART_Transmit(&KEYOUT,HandShake_ERROR,9,1000);
	//}
	//
	//if(!Con_GetChipSN())						//获取芯片序列号
	//{
	//	HAL_UART_Transmit(&KEYOUT,GetChipSN_ERROR,9,1000);
	//}
	//
	//if(!Con_CheckSensor())
	//{
	//	HAL_UART_Transmit(&KEYOUT,CheckSensor_ERROR,9,1000);
	//}
	//
	//if(!Con_ControlBLN(0x01,0x07,0x07,0x00))
	//{
	//	HAL_UART_Transmit(&KEYOUT,ControlBLN_ERROR,9,1000);
	//}
	////GetTableState();
	//Delay_ms(1000);
	////Con_AutoIdentify(ID,PARAM);
	//if(!Con_Sleep())
	//{
	//	HAL_UART_Transmit(&KEYOUT,Sleep_ERROR,9,1000);
	//}
	
	
//---------------------------------------------------------------------------------/
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==GPIO_PIN_SET)
		{
			rxstate=0;
			Con_Sleep();
			Delay_ms(2000);
		}
		
		//Delay_ms(500);
		//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		//HAL_UART_Receive(&huart1,data,10,1000);
		//Delay_ms(500);
		//HAL_UART_Transmit(&huart1,data,10,100);
		if(USART1_RX_STA&0x8000){
			HAL_UART_Transmit(&KEYOUT,RxData1,USART1_RX_STA&0X3FFF,1000);
			
			DATA_Judge(RxData1,6);
			
			USART1_RX_STA=0;
		}
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
