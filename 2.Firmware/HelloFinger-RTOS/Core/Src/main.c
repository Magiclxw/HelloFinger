/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_task_finger.h"
#include "app_task_key.h"
#include "drv_fpm383.h"
#include "sys.h"
#include "delay.h"
#include "drv_at24c64.h"
#include "drv_ch9329.h"
#include "drv_encoder.h"
#include "..\USER\driver\WS2812\drv_ws2812b.h"
#include "app_task_rgb.h"
#include "adc.h"
#include "dma.h"
#include "app_task_joystick.h"
#include "..\USER\driver\W25Q128\drv_w25q128.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
const char *Firmware_Version	= "1.0.0_beta";
#define Compile_time	__DATE__","__TIME__
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
_SYSTEM_INFO_t g_sys_info;	//系统信息
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
uint8_t rx[20] = {0};

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint16_t id = 0;
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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
	MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	
	MX_DMA_Init();	//dma初始化要在其他使用dma外设之前
	MX_ADC1_Init();
	Flash_Init();
	MX_SPI2_Init();
	delay_init(72);
	IIC_Init();
	FPM383C_Init();
	CH9329_Init();
	delay_ms(1000);
	ENCODER_Init();
	printf("hello finger\r\n");
	memcpy(g_sys_info.firmware_version,Firmware_Version,strlen(Firmware_Version));

	id = Flash_Read_id(); /* 读取FLASH ID */
	
    while ((id == 0) || (id == 0XFFFF)) /* 检测不到FLASH芯片 */
    {
        printf("FLASH Check Failed!");
        delay_ms(500);
        printf( "Please Check!      ");
        delay_ms(500);
    }
	uint8_t data[10] = {0,1,2,3,4,5,6,7,8,9};
	
	//Flash_write(data,0x10000,10);
	//AT24C64_WriteOneByte(0x00,data[2]);
	
	//delay_ms(1000);
	
	//rx[0] = AT24C64_ReadOneByte(0x00);
	//Flash_read(rx,0x100000,10);
	Flash_Read_DMA(rx,0x100000+100*2,20);
	//delay_ms(1000);
	for(uint8_t i=0;i<20;i++)
	{
		printf("data : %d\r\n",rx[i]);
	}
	
	//char hello[15] = {"hello world!!!"};
	//CH9329_Input_Ascii(hello);
	RegisterUsart1ReceiveCallBack(Key_GiveNotifyFromISR);
	RegisterUsart2ReceiveCallBack(Finger_GiveNotifyFromISR);
	RegisterADC1ReceiveCallBack(JoyStick_GiveNotifyFromISR);
	RegisterFingerTouchCallBack(Finger_TouchNotifyFromISR);
	RegisterEncoderKeyCallBack(ENCODER_KeyNotifyFromISR);
	RegisterActionKeyCallBack(Action_KeyNotifyFromISR);
	RegisterNormalKeyCallBack(Normal_KeyNotifyFromISR);
	//Generate_StoreChar(0xAB,0x01);
	Task_Create();
	vTaskStartScheduler();
	//char hello[5] = {"hello"};
	//CH9329_Input_Ascii(hello);
	//CH9329_Index_to_Ascii(hello);
	//uint8_t data[5] = {0xAB,0xCD,0xEF,0x12,0x34};
	//Send_HID_Data(data,5);
	//CH9329_Generate_KEY_CMD(KEY_TYPE_GENERAL_KEY,'T');
	//Generate_AutoEnroll(0x0001,4,AUTOENROLL_PARAM_BACKLIGHT_ON|AUTOENROLL_PARAM_PRETREATMENT_ON|AUTOENROLL_PARAM_CRITICAL_STATE_ON|AUTOENROLL_PARAM_ID_COVER_ON|AUTOENROLL_PARAM_ENROLL_REPEAT_ON|AUTOENROLL_PARAM_FINGER_MOVE_ON);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
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
