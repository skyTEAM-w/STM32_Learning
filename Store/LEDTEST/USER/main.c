#include "stm32f10x.h"
#include "LED.h"

 
/************************************************
 ALIENTEK ��ӢSTM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 void Delay(uint32_t count)
 {
	 while(count--);
 }
 int main(void)
 {
	LED_Init();
  while(1)
	{
		LED_On();
		Delay(0xA00000);
		LED_Off();
		Delay(0xA00000);
	}
 }
