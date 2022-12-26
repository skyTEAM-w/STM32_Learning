#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "wkup.h"

int main()
{
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	USART1_Init(115200);
	
	
	while(1)
	{
        printf("time:5\r\n");
        LED1 = 0;
        delay_ms(1000);
        printf("time:4\r\n");
        LED1 = 1;
        delay_ms(1000);
        printf("time:3\r\n");
        LED1 = 0;
        delay_ms(1000);
        printf("time:2\r\n");
        LED1 = 1;
        delay_ms(1000);
        printf("time:1\r\n");
        LED1 = 0;
        delay_ms(1000);
        printf("time:0\r\n");
        LED1 = 1;
        delay_ms(1000);
        
        printf("进入系统待机模式\r\n");
		Enenter_Standby_Mode();
	}
}
