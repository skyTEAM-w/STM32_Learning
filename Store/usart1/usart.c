#include "usart.h"


void NVIC_Config_UART(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//f103.h����
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�Ƿ�������ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�,����2:0-3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//��Ӧ���ȼ�
	
	NVIC_Init(&NVIC_InitStructure);//misc.h

}

void MY_UART_Init(void)
{
    //TX PA9 ����;RX->PA10 ����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    //��ʹ��GPIOʱ�Ӻʹ���ʱ��
    //RCC_APB2PeriphClockCmd(UART_CLK_Port|UARTx_CLK, ENABLE);
	  RCC_APB2PeriphClockCmd(UART_CLK_Port, ENABLE);
    RCC_APB1PeriphClockCmd(UARTx_CLK, ENABLE);
    //��GPIO��ʼ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = UARTx_Pin_TX;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UARTx_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = UARTx_Pin_RX;
    GPIO_Init(UARTx_Port, &GPIO_InitStructure);

    //�۴��ڳ�ʼ��
    USART_InitStructure.USART_BaudRate = UART_BAUDRATE;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx| USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = 1;
    USART_InitStructure.USART_WordLength = 8;
    USART_Init(UART_USER, &USART_InitStructure);

    //��ʹ�ܴ���
    USART_Cmd(UART_USER, ENABLE);
		
		//����NVIC��������
		NVIC_Config_UART();
		//ʹ�ܽ����ж�,������
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
