/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define KEY_UP HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin)
#define KEY0 HAL_GPIO_ReadPin(KY0_GPIO_Port, KY0_Pin)
#define KEY1 HAL_GPIO_ReadPin(KY1_GPIO_Port, KY1_Pin)
#define KEY2 HAL_GPIO_ReadPin(KY2_GPIO_Port, KY2_Pin)

#define KEY0_PRESS    1
#define KEY1_PRESS    2
#define KEY2_PRESS    3
#define KEY_UP_PRESS  4

//uint8_t key_mode;

void LD1_Toggle(void);
void LD0_Toggle(void);

uint8_t KEY(uint8_t mode);

void LED0_Turn_On(void);
void LED0_Turn_Off(void);
void LED1_Turn_On(void);
void LED1_Turn_Off(void);

void BEEP_Toggle(void);
void BEEP_Turn_On(void);
void BEEP_Turn_Off(void);
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

