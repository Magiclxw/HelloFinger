#include "..\USER\driver\WS2812\drv_ws2812b.h"

SPI_HandleTypeDef hspi2;

/* SPI2 init function */
void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_1LINE;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspInit 0 */

  /* USER CODE END SPI2_MspInit 0 */
    /* SPI2 clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI2 GPIO Configuration
    PB13     ------> SPI2_SCK
    PB15     ------> SPI2_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI2_MspInit 1 */

  /* USER CODE END SPI2_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspDeInit 0 */

  /* USER CODE END SPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI2_CLK_DISABLE();

    /**SPI2 GPIO Configuration
    PB13     ------> SPI2_SCK
    PB15     ------> SPI2_MOSI
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_15);

  /* USER CODE BEGIN SPI2_MspDeInit 1 */

  /* USER CODE END SPI2_MspDeInit 1 */
  }
}


/**
 * @brief     write one frame
 * @param[in] rgb is the input color
 * @param[in] *temp points to a temp buffer
 * @note      none
 */
int WS2812B_Write_One_Frame(uint32_t rgb, uint8_t temp[48])
{
    uint8_t r, g, b;
    uint8_t i, j;
    uint32_t c, point;
    const uint16_t one_code = 0xFFF8U;
    const uint16_t zero_code = 0xE000U;
    
    r = (uint8_t)((rgb >> 16) & 0xFF);                               /* set red */
    g = (uint8_t)((rgb >> 8) & 0xFF);                                /* set green */
    b = (uint8_t)((rgb >> 0) & 0xFF);                                /* set blue */
    c = ((uint32_t)(g) << 16) | ((uint32_t)(r) << 8) | b;            /* set color */
    
    memset(temp, 0, sizeof(uint8_t) * 30);                           /* clear the temp buffer */
    
    point = 0;                                                       /* clear point */
    for (i = 0; i < 24; i++)                                         /* set 24 bit */
    {
        if (((c >> (23 - i)) & 0x01) != 0)                           /* if bit 1 */
        {
            for (j = 0; j < 16; j ++)                                /* 16 bit */
            {
                if (((one_code >> (15 - j)) & 0x01) != 0)            /* if one code */
                {
                    temp[point / 8] |= 1 << (7 - (point % 8));       /* set bit 1 */
                }
                else
                {
                    temp[point / 8] |= 0 << (7 - (point % 8));       /* set bit 0 */
                }
                point = point + 1;                                   /* point++ */
            }
        }
        else                                                         /* if bit 0 */
        {
            for (j = 0; j < 16; j ++)                                /* 16 bit */
            {
                if (((zero_code >> (15 - j)) & 0x01) != 0)           /* if zero code */
                {
                    temp[point / 8] |= 1 << (7 - (point % 8));       /* set bit 1 */
                }
                else
                {
                    temp[point / 8] |= 0 << (7 - (point % 8));       /* set bit 0 */
                }
                point = point + 1;                                   /* point++ */
            }
        }
    }
}

/**
 * @brief     write reset and color frame
 * @param[in] *handle points to a ws2812b handle structure
 * @param[in] *rgb points to a rgb color buffer
 * @param[in] len is the rgb length
 * @param[in] *temp points to a temp buffer
 * @param[in] temp_len is the temp buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write command failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 rgb is null
 *            - 5 temp is null
 *            - 6 temp buffer is too small
 * @note      none
 */
int WS25812B_write(uint32_t *rgb, uint32_t len, uint8_t *temp)
{
    uint32_t i, bit_size = WS2812_NUM * 8;
    
    for (i = 0; i < bit_size; i++)                                          /* set the reset frame */
    {
        temp[i] = 0x00;                                                     /* set 0x00 */
    }
    HAL_SPI_Transmit(&hspi2, temp, (uint16_t)bit_size, 1000);              /* write command */
    
    bit_size = 24 * 16 * len ;                                              /* set the bit size */
    bit_size = bit_size / 8;                                                /* set the bit size */

    for (i = 0; i < len; i++)                                               /* set the color frame */
    {
        WS2812B_Write_One_Frame(rgb[i], &temp[i * 48]);                   /* set color */
    }
    
    HAL_SPI_Transmit(&hspi2, temp, (uint16_t)bit_size, 1000);               /* write command */
}

/**
 * @brief     write the reset frame
 * @param[in] *handle points to a ws2812b handle structure
 * @param[in] *temp points to a temp buffer
 * @param[in] temp_len is the temp buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write command failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 temp is null
 *            - 5 temp buffer is too small
 * @note      none
 */
uint8_t WS2812B_Write_Only_Reset(uint8_t *temp, uint32_t temp_len)
{
    uint32_t i, bit_size;
    

    
    bit_size = 144;                                 /* set the bit size */
    bit_size = bit_size / 8;                                                /* set the bit size */
    if (bit_size > temp_len)                                                /* check temp length */
    {
			
    }
    
    for (i = 0; i < bit_size; i++)                                          /* set the reset frame */
    {
        temp[i] = 0x00;                                                     /* set 0x00 */
    }
    
    if (HAL_SPI_Transmit(&hspi2, temp, (uint16_t)bit_size, 1000) != HAL_OK)               /* write command */
    {
			
    }

}

/**
 * @brief     write the color frame
 * @param[in] *handle points to a ws2812b handle structure
 * @param[in] *rgb points to a rgb color buffer
 * @param[in] len is the rgb length
 * @param[in] *temp points to a temp buffer
 * @param[in] temp_len is the temp buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write command failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 rgb is null
 *            - 5 temp is null
 *            - 6 temp buffer is too small
 * @note      none
 */
uint8_t WS2812B_Write_Only_Color(uint32_t *rgb, uint32_t len, uint8_t *temp, uint32_t temp_len)
{
    uint32_t i, bit_size;

    bit_size = 24 * 16 * len ;                                              /* set the bit size */
    bit_size = bit_size / 8;                                                /* set the bit size */
    if (bit_size > temp_len)                                                /* check temp length */
    {
			
    }
   
    for (i = 0; i < len; i++)                                               /* set the color frame */
    {
        WS2812B_Write_One_Frame(rgb[i], &temp[i * 48]);                   /* set color */
    }
    
    if (HAL_SPI_Transmit(&hspi2, temp, (uint16_t)bit_size, 1000) != HAL_OK)               /* write command */
    {
			
    }

}

