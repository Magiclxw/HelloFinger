#ifndef _DRV_WS2812B_H
#define _DRV_WS2812B_H

#include "sys_config.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define WS2812_NUM 6


void MX_SPI2_Init(void);
int WS25812B_write(uint32_t *rgb, uint32_t len, uint8_t *temp);

#endif