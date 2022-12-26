#include "wkup.h"

void Enenter_Standby_Mode(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    PWR_WakeUpPinCmd(ENABLE);
    PWR_ClearFlag(PWR_FLAG_WU);
    PWR_EnterSTANDBYMode();
}
