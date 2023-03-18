#include "delay.h"

static uint32_t clk_us = 0;

void Delay_Init(void)
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	clk_us = 72;
}

void Delay_us(uint32_t us)
{
	uint32_t ticks = 0;
	uint32_t t_old,t_now,t_cnt = 0;
	uint32_t reload = SysTick->LOAD;
	ticks = us*clk_us;
	t_old = SysTick->VAL;
	while(1){
		t_now = SysTick->VAL;
		if(t_now != t_old){
			if(t_now < t_old){
				t_cnt += t_old-t_now;
			}else{
				t_cnt += reload - t_old + t_now;
			}
			t_old = t_now;
			if(t_cnt >= ticks) break;
		}
	}
}

void Delay_ms(uint16_t ms)
{
	for(uint32_t i = 0;i<ms;i++){
		Delay_us(1000);
	}
}
