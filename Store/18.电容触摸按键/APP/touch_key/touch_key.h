#ifndef __TOUCH_KEY_H__
#define __TOUCH_KEY_H__

#include "system.h"

#define TOUCH_Port  GPIOA
#define TOUCH_Pin   GPIO_Pin_1
#define TOUCH_RCC   RCC_APB2Periph_GPIOA

void TIM5_CH2_Input_Init(u16 arr,u16 psc);
u16 TOUCH_Get_Val(void);
u8 TOUCH_KEY_Init(u16 pcs);
u8 TOUCH_KEY_Scan(u8 mode);

#endif
