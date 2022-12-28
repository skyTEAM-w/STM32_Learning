#ifndef __ADC_H__
#define __ADC_H__

#include "system.h"

void ADCx_Init(void);
u16 Get_ADC_Value(u8 ch, u8 times);

#endif
