#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "lsens.h"

int main()
{
    u8 i = 0;
    u8 lsens_value = 0;
    
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	USART1_Init(115200);
    Lsens_Init();
	
	while(1)
	{
        i++;
        if (i % 20 == 0)
        {
            LED1 = !LED1;
        }
        delay_ms(10);
        
        if (i % 100 == 0)
        {
            lsens_value = Lsens_Get_Value();
            printf("π‚’’«ø∂» %d\r\n", lsens_value);
        }
	}
}
