#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "adc.h"

int main()
{
    u8 i = 0;
    u16 value = 0;
    float vol;
    
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	USART1_Init(115200);
	ADCx_Init();
	
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
            value = Get_ADC_Value(ADC_Channel_1, 20);
            printf("检测的AD值为 %d\r\n", value);
            vol = (float)value * (3.3 / 4096);
            printf("检测的电压值为 %.2fV\r\n", vol);
        }
	}
}
