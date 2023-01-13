#include "dac.h"

void DAC1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitSturcture;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    DAC_InitSturcture.DAC_Trigger = DAC_Trigger_None;
    DAC_InitSturcture.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitSturcture.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    DAC_InitSturcture.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
    DAC_Init(DAC_Channel_1, &DAC_InitSturcture);
    
    DAC_SetChannel1Data(DAC_Align_12b_R, 0);
    
    DAC_Cmd(DAC_Channel_1, ENABLE);
}
