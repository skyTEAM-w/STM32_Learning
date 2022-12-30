#include "lsens.h"
#include "SysTick.h"

void Lsens_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3 | RCC_APB2Periph_GPIOF, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC3, &ADC_InitStructure);
    
    ADC_Cmd(ADC3, ENABLE);
    
    ADC_ResetCalibration(ADC3);
    while (ADC_GetResetCalibrationStatus(ADC3));
    ADC_StartCalibration(ADC3);
    while (ADC_GetCalibrationStatus(ADC3));
    
    ADC_SoftwareStartConvCmd(ADC3, ENABLE);
}

u16 Get_ADC3(u8 ch)
{
    ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_239Cycles5);
  
    ADC_SoftwareStartConvCmd(ADC3, ENABLE);
    while (!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC));
    
    return ADC_GetConversionValue(ADC3);
}

#define LSENS_READ_TIMES    10

u8 Lsens_Get_Value(void)
{
    u8 t = 0;
    u32 temp_val = 0;
    
    for (t = 0; t < LSENS_READ_TIMES; t++)
    {
        temp_val += Get_ADC3(ADC_Channel_6);
        delay_ms(5);
    }
    temp_val /= LSENS_READ_TIMES;
    
    if (temp_val > 4000)
    {
        temp_val = 4000;
    }
    
    return 100 - temp_val / 40;
}
