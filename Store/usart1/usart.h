#ifndef __STM32F10X_UART_H__
#define __STM32F10X_UART_H__

#include "stm32f10x.h"
#include <stdio.h>

#define UART_PRINTF       USART2
#define UART_SCANF        USART2
#define UART_CLK_Port     RCC_APB2Periph_GPIOA
#define UARTx_CLK         RCC_APB1Periph_USART2
#define UARTx_Port        GPIOA
#define UARTx_Pin_TX      GPIO_Pin_2
#define UARTx_Pin_RX      GPIO_Pin_3
#define UART_USER         USART2
#define UART_BAUDRATE     9600

void NVIC_Config_UART(void);
void MY_UART_Init(void);
void UART_SendByte(USART_TypeDef* USARTx, uint8_t data);
void UART_SendString(USART_TypeDef* USARTx, char* string);

#endif