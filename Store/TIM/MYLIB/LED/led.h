#ifndef __STM32F10X_LED_H__
#define __STM32F10X_LED_H__

#include "stm32f10x.h"
#include "delay.h"

#define GPIO_Pin_LED 				      GPIO_Pin_5
#define GPIOLED						        GPIOA
#define RCC_APB2Periph_GPIOLED		RCC_APB2Periph_GPIOA

extern uint16_t LED_State;

void LED_Init(void);
void LED_Blink(u16);
void LED_Turn_On(void);
void LED_Turn_Off(void);

#endif
