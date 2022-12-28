#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "dac.h"
#include "key.h"


int main()
{
    u8 i = 0;
    u8 key = 0;
    int dac_value = 0;
    float dac_vol;
    u16 dac_val = 0;
    
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	USART1_Init(115200);
    DAC1_Init();
    KEY_Init();
	
	while(1)
	{
        key = KEY_Scan(0);
        if (key == KEY_UP_PRESS)
        {
            dac_value += 400;
            if (dac_value >= 4000)
            {
                dac_value = 4095;
            }
            DAC_SetChannel1Data(DAC_Align_12b_R, dac_value);
        }
        else if (key == KEY1_PRESS)
        {
            dac_value -= 400;
            if (dac_value <= 0)
            {
                dac_value = 0;
            }
            DAC_SetChannel1Data(DAC_Align_12b_R, dac_value);
        }
        
        i++;
        if (i % 20 == 0)
        {
            LED1 = !LED1;
        }
        delay_ms(10);
        
        if (i % 100 == 0)
        {
            dac_val = DAC_GetDataOutputValue(DAC_Channel_1);
            dac_vol = 3.3 * (float)dac_val / 4095;
            printf("DACµçÑ¹Îª %.2f\r\n", dac_vol);
        }
	}
}
