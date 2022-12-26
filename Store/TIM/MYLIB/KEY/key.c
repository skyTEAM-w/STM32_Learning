#include "key.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOKEY, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_KEY;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOKEY, &GPIO_InitStructure);
}

void KEY_Scan(void)
{
	if (!KEY)
	{
		delay_ms(20);
		if(!KEY)
		{
			key_cnt++;
			if(key_cnt == 3)
				key_cnt = 0;
		}
		while(!KEY);
	}
}
