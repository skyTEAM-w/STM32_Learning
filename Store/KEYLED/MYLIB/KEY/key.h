#ifndef __STM32F10X_KEY_H__
#define __STM32F10X_KEY_H__

#include "stm32f10x.h"
#include "delay.h"

#define GPIO_Pin_KEY 				GPIO_Pin_13
#define GPIOKEY						GPIOC
#define RCC_APB2Periph_GPIOKEY		RCC_APB2Periph_GPIOC

#define KEY							GPIO_ReadInputDataBit(GPIOKEY, GPIO_Pin_KEY)

extern u8 key_cnt;

void KEY_Init(void);
void KEY_Scan(void);

#endif