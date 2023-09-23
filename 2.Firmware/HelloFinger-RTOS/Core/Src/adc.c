#include "adc.h"
#include "queue.h"
#include "app_task_joystick.h"
#include "drv_ch9329.h"

uint16_t value_X_Y[2] = {0};
/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

FUNC_USARTRECVTCB ADCREADYCallback = NULL;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PB0     ------> ADC1_IN8
    PB1     ------> ADC1_IN9
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA1_Channel1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_NORMAL;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PB0     ------> ADC1_IN8
    PB1     ------> ADC1_IN9
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_1);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	
	//BaseType_t xHigherPriorityTaskWoken = pdTRUE;
	////printf("x = %d y = %d\r\n",value_X_Y[0],value_X_Y[1]);
	//uint8_t move_dist_x = 0;	//x方向移动距离
	//uint8_t move_dist_y = 0;	//y方向移动距离
	//uint8_t move_dist_x_y[2] = {0};
	//uint8_t offset_X = value_X_Y[0]/50;
	//uint8_t offset_Y = value_X_Y[1]/50;
	//
	////printf("x = %d y = %d\r\n",offset_X,offset_Y);
	//if(offset_X < MIN_OFFSET){
	//	move_dist_x = (MIN_OFFSET - offset_X)*1;
	//}
	//if(offset_X > MAX_OFFSET){
	//	move_dist_x = 0xFF - ((offset_X - MAX_OFFSET)*1);
	//}
	//if(offset_Y < MIN_OFFSET){
	//	move_dist_y = (MIN_OFFSET - offset_Y)*1;
	//}
	//if(offset_Y > MAX_OFFSET){
	//	move_dist_y = 0xFF - ((offset_Y - MAX_OFFSET)*1);
	//}
	//if(move_dist_x != 0 | move_dist_y != 0){
	//	//REL_Mouse_Ctrl(0,move_dist_x,move_dist_y,button_NULL);
	//	//move_dist_x_y[0] = move_dist_x;
	//	//move_dist_x_y[1] = move_dist_y;
	//	xQueueSendFromISR(Queue_JOYSTICKProcessing_Handle,move_dist_x_y,&xHigherPriorityTaskWoken);
	//	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	//	//xQueueSend(Queue_JOYSTICKProcessing_Handle,move_dist_x_y,0);
	//}
	//uint8_t move_dist_x = 0;	//x方向移动距离
	//uint8_t move_dist_y = 0;	//y方向移动距离
	uint8_t move_dist_x_y[2] = {0};
	move_dist_x_y[0] = value_X_Y[0]/50;
	move_dist_x_y[1] = value_X_Y[1]/50;
	//printf("x = %d y = %d\r\n",value_X_Y[0],value_X_Y[1]);
	if(ADCREADYCallback != NULL)
	{
		ADCREADYCallback(move_dist_x_y,2);
	}
}

int RegisterADC1ReceiveCallBack(FUNC_USARTRECVTCB ADC1READYVCBT)
{
	ADCREADYCallback = ADC1READYVCBT;
	return OPERATE_SUCCESS;
}
/* USER CODE END 1 */
