#include "usart.h"

void NVIC_Config_UART(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&NVIC_InitStruct);
}

void MY_UART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	RCC_APB2PeriphClockCmd(UART_CLK_Port, ENABLE);
	RCC_APB1PeriphClockCmd(UARTx_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = UARTx_Pin_TX;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UARTx_Port, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = UARTx_Pin_RX;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UARTx_Port, &GPIO_InitStruct);
	
	USART_InitStruct.USART_BaudRate = UART_BAUDRATE;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = 1;
	USART_InitStruct.USART_WordLength = 8;
	USART_Init(UART_USER, &USART_InitStruct);
	
	USART_Cmd(UART_USER, ENABLE);
	NVIC_Config_UART();
	USART_ITConfig(UART_USER, USART_IT_RXNE, ENABLE);
}

void UART_SendByte(USART_TypeDef* USARTx, uint8_t data)
{
	USART_SendData(UART_USER, data);
	while(!USART_GetFlagStatus(UART_USER, USART_FLAG_TC));
}

void UART_SendString(USART_TypeDef* USARTx, char* string)
{
	char* str = string;
	while(*str)
	{
		UART_SendByte(USARTx, *str);
		str ++;
	}
}
