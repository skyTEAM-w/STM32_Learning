#include "tim.h"
#include "led.h"

void TIM2_Int_Init(uint16_t arr, uint16_t psc)
{
  TIM_TimeBaseInitTypeDef TIM_InitBaseStruct;
  NVIC_InitTypeDef NVIC_InitStruct;
  
  TIM_InitBaseStruct.TIM_Prescaler = psc;
  TIM_InitBaseStruct.TIM_Period = arr;
  TIM_InitBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_InitBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
  TIM_TimeBaseInit(TIM2, &TIM_InitBaseStruct);
  
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  
  NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x03;
  
  NVIC_Init(&NVIC_InitStruct);
  
  TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
  {
    LED_State = !LED_State;
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
  }
}
