#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "touch_key.h"


/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main()
{
	u8 i=0;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	LED_Init();
	USART1_Init(115200);
	Touch_Key_Init(6);   //����Ƶ��Ϊ12M
	
	while(1)
	{
		if(Touch_Key_Scan(0)==1)
		{
			LED2=!LED2;
		}
		
		i++;
		if(i%20==0)
		{
			LED1=!LED1;
		}
		delay_ms(10);
	}
}
