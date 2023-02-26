#include "delay.h"
#include "stm32f1xx.h"


static uint32_t fac_us=0;

void Delay_Init(void)
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	fac_us=72;
}

void Delay_us(uint32_t us)
{
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;  	 
	ticks=us*fac_us;
	told=SysTick->VAL;
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;
		}  
	}
}

void Delay_ms(uint16_t ms)
{
	uint32_t i;
	for(i=0;i<ms;i++) Delay_us(1000);
}
