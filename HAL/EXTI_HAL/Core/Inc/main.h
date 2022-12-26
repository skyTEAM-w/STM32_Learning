/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KY2_Pin GPIO_PIN_2
#define KY2_GPIO_Port GPIOE
#define KY2_EXTI_IRQn EXTI2_IRQn
#define KY1_Pin GPIO_PIN_3
#define KY1_GPIO_Port GPIOE
#define KY1_EXTI_IRQn EXTI3_IRQn
#define KY0_Pin GPIO_PIN_4
#define KY0_GPIO_Port GPIOE
#define KY0_EXTI_IRQn EXTI4_IRQn
#define LD1_Pin GPIO_PIN_5
#define LD1_GPIO_Port GPIOE
#define KEY_UP_Pin GPIO_PIN_0
#define KEY_UP_GPIO_Port GPIOA
#define KEY_UP_EXTI_IRQn EXTI0_IRQn
#define LD0_Pin GPIO_PIN_5
#define LD0_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_8
#define BEEP_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define __DEBUG__
#ifdef __DEBUG__
#define LOG(fmt, ...) printf("[LOG]:" fmt "\r\n", ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) printf("[WARNING]:" fmt "\r\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) printf("[ERROR]:%s:%d:" fmt "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
#elif
#define LOG(fmt, ...)
#define LOG_WARNING(fmt, ...)
#define LOG_ERROR(fmt, ...)
#endif
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
