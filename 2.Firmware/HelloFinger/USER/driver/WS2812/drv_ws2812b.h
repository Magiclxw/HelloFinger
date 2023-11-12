#ifndef _DRV_WS2812B_H
#define _DRV_WS2812B_H

#include "sys_config.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define WS2812_NUM 6


int MX_SPI2_Init(void);
int WS25812B_write(uint32_t *rgb, uint32_t len, uint8_t *temp);
uint8_t WS2812B_Write_Only_Reset(uint8_t *temp, uint32_t temp_len);

#endif
