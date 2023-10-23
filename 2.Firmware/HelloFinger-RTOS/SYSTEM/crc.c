#include "crc.h"
#include "stdlib.h"

CRC_HandleTypeDef crc;

void CRC_Init(void)
{
  /* 外设时钟使能 */
  __HAL_RCC_CRC_CLK_ENABLE();
  crc.Instance = CRC;
  HAL_CRC_Init(&crc);
}

uint32_t Calc_CRC(uint8_t *data,uint8_t len)
{
	uint32_t crc_value = 0;
	
	uint8_t switch_len = 0;
	switch_len = len/4;
	if(len%4) switch_len ++;
	
	crc_value = HAL_CRC_Calculate(&crc,(uint32_t*)data,switch_len);
	
	return crc_value;
}

