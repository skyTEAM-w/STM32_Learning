#include "usart.h"


void NVIC_Config_UART(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//f103.h里面
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//是否开启这个中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级,分组2:0-3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//响应优先级
	
	NVIC_Init(&NVIC_InitStructure);//misc.h

}

void MY_UART_Init(void)
{
    //TX PA9 发送;RX->PA10 接收
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    //①使能GPIO时钟和串口时钟
    //RCC_APB2PeriphClockCmd(UART_CLK_Port|UARTx_CLK, ENABLE);
	  RCC_APB2PeriphClockCmd(UART_CLK_Port, ENABLE);
    RCC_APB1PeriphClockCmd(UARTx_CLK, ENABLE);
    //②GPIO初始化
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = UARTx_Pin_TX;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UARTx_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = UARTx_Pin_RX;
    GPIO_Init(UARTx_Port, &GPIO_InitStructure);

    //③串口初始化
    USART_InitStructure.USART_BaudRate = UART_BAUDRATE;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx| USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = 1;
    USART_InitStructure.USART_WordLength = 8;
    USART_Init(UART_USER, &USART_InitStructure);

    //④使能串口
    USART_Cmd(UART_USER, ENABLE);
		
		//配置NVIC，接收用
		NVIC_Config_UART();
		//使能接收中断,接收用
		USART_ITConfig(UART_USER, USART_IT_RXNE, ENABLE);
}

void UART_SendByte(USART_TypeDef* USARTx, uint8_t data)
{
    USART_SendData(USARTx, data);
    while(! USART_GetFlagStatus(UART_USER, USART_FLAG_TC));
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
