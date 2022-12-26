#include "stm32f10x.h"
#include "delay.h"
#include "KEY.h"
#include "LED.h"
#include "TIM.h"

/************************************************
 WUT-电子科技协会STM32培训工程模板
 采用开发板：NUCLEO-F103RB
 SYSTEM文件中采用的是正点原子的程序
 本模板只做教学使用，无商业用途
************************************************/


// void Delay(u32 count)
// {
//   u32 i=0;
//   for(;i<count;i++);
// }

u8 key_cnt = 0;
uint16_t LED_State = 0;

 int main(void)
 {
   LED_Init();
   KEY_Init();
   delay_init();
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   TIM2_Int_Init(9999, 7199);
   
  while(1)
	{
    GPIO_WriteBit(GPIOLED, GPIO_Pin_LED, LED_State);
	}
 }
 

