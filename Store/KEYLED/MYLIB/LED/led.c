#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOLED, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_LED);
}

void LED_Blink(u16 ms)
{
	GPIO_SetBits(GPIOLED, GPIO_Pin_LED);
	delay_ms(ms);
	GPIO_ResetBits(GPIOLED, GPIO_Pin_LED);
	delay_ms(ms);
}

void LED_Turn_On(void)
{
	GPIO_SetBits(GPIOLED,GPIO_Pin_LED);
}


void LED_Turn_Off(void)
{
	GPIO_ResetBits(GPIOLED, GPIO_Pin_LED);
}