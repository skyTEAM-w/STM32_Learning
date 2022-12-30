#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "dac.h"
#include "key.h"
#include "dma.h"


#define SEND_BUFFER_LENGTH  5000
u8 Send_Buffer[SEND_BUFFER_LENGTH];

void Send_Data(u8 *p)
{
    u16 i = 0;
    for (i = 0; i < SEND_BUFFER_LENGTH; i++)
    {
        *p = '5';
        p++;
    }
}

int main()
{
    u8 i = 0;
    u8 key = 0;
    
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	USART1_Init(115200);
    KEY_Init();
    DMAx_Init(DMA1_Channel4, (u32)&USART1->DR, (u32)Send_Buffer, SEND_BUFFER_LENGTH);
    Send_Data(Send_Buffer);
	
	while(1)
	{
        key = KEY_Scan(0);
        if (key == KEY_UP_PRESS)
        {
            USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
            DMAx_Enable(DMA1_Channel4, SEND_BUFFER_LENGTH);
            
            while(1)
            {
                if (DMA_GetFlagStatus(DMA1_FLAG_TC4) != 0)
                {
                    DMA_ClearFlag(DMA1_FLAG_TC4);
                    break;
                }
                LED2 = !LED2;
                delay_ms(300);
            }
        }
        
        i++;
        if (i % 20 == 0)
        {
            LED1 = !LED1;
        }
        delay_ms(10);
	}
}
