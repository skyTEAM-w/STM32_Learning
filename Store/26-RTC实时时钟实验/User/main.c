#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "rtc.h"

int main()
{
    u8 i = 0;
    
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	USART1_Init(115200);
    RTC_Init();
	
	while(1)
	{
        i++;
        if (i % 20 == 0)
        {
            LED1 = !LED1;
        }
        delay_ms(10);
	}
}
