#include "stm32f10x.h"
#include "delay.h"

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
 int main(void)
 {	
  GPIO_InitTypeDef  GPIO_InitStructure;
	 
	delay_init();
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	    //使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;			    //LED-->PA.5 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);			     //初始化GPIOA.5
  GPIO_SetBits(GPIOA,GPIO_Pin_5);					//PA.5 输出高  
  while(1)
	{
	    GPIO_ResetBits(GPIOA,GPIO_Pin_5);
//		  Delay(3000000);
			delay_ms(500);
		  GPIO_SetBits(GPIOA,GPIO_Pin_5);
//		Delay(3000000);
			delay_ms(500);
	}
 }
