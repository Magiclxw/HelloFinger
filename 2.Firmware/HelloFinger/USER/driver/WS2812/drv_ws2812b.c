#include "drv_ws2812b.h"

SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_tx;

/* SPI2 init function */
int MX_SPI2_Init(void)
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
	__HAL_SPI_ENABLE(&hspi2);
  /* USER CODE END SPI2_Init 2 */
	return OPERATE_SUCCESS;
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


int WS25812B_write(uint32_t *rgb, uint32_t len, uint8_t *temp)
{
    uint32_t i, bit_size = 288;	//(16*24*6)/8;
    
    memset(temp,0,288);
	
    //HAL_SPI_Transmit_DMA(&hspi2, temp, 288);              /* write command */
                                                   /* set the bit size */
		//HAL_SPI_Transmit(&hspi2, temp, 288,1000);
    for (i = 0; i < len; i++)                                               /* set the color frame */
    {
        WS2812B_Write_One_Frame(rgb[i], &temp[i * 48]);                   /* set color */
    }
		
    HAL_SPI_Transmit_DMA(&hspi2, temp, 288);               /* write command */
		//HAL_SPI_Transmit(&hspi2, temp, 288,1000);
}


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

