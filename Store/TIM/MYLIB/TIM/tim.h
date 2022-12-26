#ifndef __STM32_TIM_H__
#define __STM32_TIM_H__

#include "stm32f10x.h"

void TIM2_Int_Init(uint16_t arr, uint16_t psc);
void TIM2_IRQHanlder(void);

#endif
