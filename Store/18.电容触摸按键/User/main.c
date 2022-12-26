#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "touch_key.h"

/*******************************************************************************
 * 函 数 名         : main
 * 函数功能		   : 主函数
 * 输    入         : 无
 * 输    出         : 无
 *******************************************************************************/
int main()
{
	u8 i = 0;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断优先级分组 分2组
	LED_Init();
	USART1_Init(115200);
	TOUCH_KEY_Init(6);

	while (1)
	{
		if (TOUCH_KEY_Scan(0) == 1)
		{
			LED2 = !LED2;
		}

		i++;
		if(i % 20 == 0)
		{
			LED1 = !LED1;
		}
		delay_ms(10);
	}
}
