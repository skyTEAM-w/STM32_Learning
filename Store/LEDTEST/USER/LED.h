#ifndef __LED_H__
#define __LED_H__
#include "stm32f10x.h"

#define LED_GPIO_PORT	GPIOA
#define LED_GPIO_PIN	GPIO_Pin_13

void LED_Init(void);
void LED_On(void);
void LED_Off(void);

#endif