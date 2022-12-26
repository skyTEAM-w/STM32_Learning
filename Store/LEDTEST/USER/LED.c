#include "LED.h"

void LED_Init(void) {
	GPIO_InitTypeDef GPIO_Init_Struct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//¿ªÆôÊ±ÖÓ
	GPIO_Init_Struct.GPIO_Pin = LED_GPIO_PIN;
	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(LED_GPIO_PORT, &GPIO_Init_Struct);
}

void LED_On(void) {
	GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
}

void LED_Off(void) {
	GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
}