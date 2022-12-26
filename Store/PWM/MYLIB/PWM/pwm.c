#include "pwm.h"
#include "led.h"

void TIM2_PWM_Init(uint16_t arr, uint16_t psc)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_InitBaseStruct;
  NVIC_InitTypeDef NVIC_InitStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  TIM_InitBaseStruct.TIM_Prescaler = psc;
  TIM_InitBaseStruct.TIM_Period = arr;
  TIM_InitBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_InitBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM2, &TIM_InitBaseStruct);
  
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputNState_Enable;
  TIM_OCInitStruct.TIM_Pulse = 0;
  TIM_OC3Init(TIM2, &TIM_OCInitStruct);
  
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
  
  TIM_Cmd(TIM2, ENABLE);
}