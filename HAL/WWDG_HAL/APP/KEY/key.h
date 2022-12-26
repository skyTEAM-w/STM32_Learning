#ifndef __STM32_KEY_H__
#define __STM32_KEY_H__

#include "gpio.h"

#define KEY_UP HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin)
#define KEY0 HAL_GPIO_ReadPin(KY0_GPIO_Port, KY0_Pin)
#define KEY1 HAL_GPIO_ReadPin(KY1_GPIO_Port, KY1_Pin)
#define KEY2 HAL_GPIO_ReadPin(KY2_GPIO_Port, KY2_Pin)

#define KEY0_PRESS    1
#define KEY1_PRESS    2
#define KEY2_PRESS    3
#define KEY_UP_PRESS  4

uint8_t KEY(uint8_t mode);

#endif
