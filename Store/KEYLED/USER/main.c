#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include <stdio.h>

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

typedef void (*pFunc) (void);

 int main(void)
 {	
	 pFunc LED_Mode = NULL;
	 delay_init();
	 LED_Init();
	 KEY_Init();
	 while(1)
	 {
		 KEY_Scan();
		 LED_Mode = key_cnt == 0 ? LED_Blink : (key_cnt == 1 ? LED_Turn_On : LED_Turn_Off);
		 LED_Mode();
	 }
 }
