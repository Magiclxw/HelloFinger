#include "drv_joystick.h"

uint16_t value_X_Y[2] = {0};
/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;


FUNC_USARTRECVTCB ADCREADYCallback = NULL;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};
	ADC_AnalogWDGConfTypeDef wdg = {0};
  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
	
	wdg.Channel = ADC_CHANNEL_8|ADC_CHANNEL_9;
	wdg.HighThreshold = DEFAULT_HIGH_THRESHOLD;
	wdg.LowThreshold = DEFAULT_LOW_THRESHOLD; 
	wdg.ITMode = ENABLE;
	wdg.WatchdogMode = ADC_ANALOGWATCHDOG_ALL_REG;
	wdg.WatchdogNumber = 0;
	HAL_ADC_AnalogWDGConfig(&hadc1,&wdg);

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
	HAL_NVIC_SetPriority(ADC1_2_IRQn, 10, 0);
  HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
  /* USER CODE END ADC1_Init 2 */

}

int RegisterADC1ReceiveCallBack(FUNC_ADCRECVTCB ADC1READYVCBT)
{
	ADCREADYCallback = ADC1READYVCBT;
	return OPERATE_SUCCESS;
}







