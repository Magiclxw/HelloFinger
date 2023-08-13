/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_ws2812b_interface_template.c
 * @brief     driver ws2812b interface template source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-11-13
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/11/13  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "ws2812b_interface.h"
#include "spi.h"
#include "delay.h"

/**
 * @brief  interface spi 10mhz bus init
 * @return status code
 *         - 0 success
 *         - 1 spi init 10mhz failed
 * @note   none
 */
uint8_t ws2812b_interface_spi_10mhz_init(void)
{
	MX_SPI2_Init();
  return 0;
}

/**
 * @brief  interface spi bus deinit
 * @return status code
 *         - 0 success
 *         - 1 spi deinit failed
 * @note   none
 */
uint8_t ws2812b_interface_spi_deinit(void)
{   
	HAL_SPI_MspDeInit(&hspi2);
  return 0;
}

/**
 * @brief     interface spi bus write command
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t ws2812b_interface_spi_write_cmd(uint8_t *buf, uint16_t len)
{
	uint8_t res = 0;
	
	res = HAL_SPI_Transmit(&hspi2, buf, len, 1000);
	
	if(res != HAL_OK) return 1;
	
  return 0;
}

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void ws2812b_interface_delay_ms(uint32_t ms)
{
	Delay_ms(ms);
}

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void ws2812b_interface_debug_print(const char *const fmt, ...)
{
    
}
