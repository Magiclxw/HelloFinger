#include "crc.h"
#include "stdlib.h"
#include "string.h"

CRC_HandleTypeDef crc;

void CRC_Init(void)
{
  __HAL_RCC_CRC_CLK_ENABLE();
  crc.Instance = CRC;
  HAL_CRC_Init(&crc);
}

uint32_t Calc_CRC(uint8_t *data,uint8_t len)
{
	uint32_t crc_value = 0;
	uint8_t remain = 0;
	uint32_t buf[100] = {0};
	
	uint8_t switch_len = 0;
	switch_len = len/4;
	memcpy(buf,data,len);
	if(len%4) switch_len++;
	remain = len%4;
	buf[switch_len] &= 0xFFFFFFFF<<(remain*8);
	crc_value = HAL_CRC_Calculate(&crc,buf,switch_len);
	
	return crc_value;
}

