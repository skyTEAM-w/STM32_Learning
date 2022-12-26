#include "touch_key.h"
#include "SysTick.h"
#include "usart.h"

#define TOUCH_ARR_MAX_VAL 0xFFFF

u16 touch_default_val = 0;

/**
 * @brief TIM5_CH2输入捕获初始化
 *
 * @param arr
 * @param psc
 */
void TIM5_CH2_Input_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //使能TIM5时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;              //管脚设置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置下拉输入模式
    GPIO_Init(GPIOA, &GPIO_InitStructure);           /* 初始化GPIO */

    TIM_TimeBaseInitStructure.TIM_Period = arr;    //自动装载值
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc; //分频系数
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //设置向上计数模式
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;                //通道2
    TIM_ICInitStructure.TIM_ICFilter = 0x00;                        //滤波
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;     //捕获极性
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;           //分频系数
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //直接映射到TI1
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ITConfig(TIM5, TIM_IT_Update | TIM_IT_CC1, ENABLE);

    TIM_Cmd(TIM5, ENABLE); //使能定时器
}

void TOUCH_Reset(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);

    delay_ms(5);
    TIM_ClearFlag(TIM5, TIM_FLAG_CC2 | TIM_FLAG_Update);
    TIM_SetCounter(TIM5, 0);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

u16 TOUCH_Get_Val(void)
{
    TOUCH_Reset();
    while (TIM_GetFlagStatus(TIM5, TIM_FLAG_CC2) == 0)
    {
        if (TIM_GetCounter(TIM5) > TOUCH_ARR_MAX_VAL - 500)
        {
            return TIM_GetCounter(TIM5);
        }
    }
    return TIM_GetCapture2(TIM5);
}

u8 TOUCH_KEY_Init(u16 pcs)
{
    u8 i, j;
    u16 buf[10];
    u32 temp;
    TIM5_CH2_Input_Init(TOUCH_ARR_MAX_VAL, pcs);
    for (i = 0; i < 10; i++)
    {
        buf[i] = TOUCH_Get_Val();
        delay_ms(10);
    }

    for (i = 0; i < 9; i++)
    {
        for (j = i + 1; j < 10; j++)
        {
            if (buf[i] > buf[j])
            {
                temp = buf[j];
                buf[j] = buf[i];
                buf[i] = temp;
            }
        }
    }

    temp = 0;
    for (i = 2; i < 8; i++)
    {
        temp += buf[i];
    }
    touch_default_val = temp / 6;
    printf("touch_def_val = %d\r\n", touch_default_val);
    if (touch_default_val > TOUCH_ARR_MAX_VAL / 2)
    {
        return 1;
    }
    else
        return 0;
}

u16 TOUCH_Get_MaxVal(u8 n)
{
    u16 temp = 0;
    u16 res = 0;
    while (n--)
    {
        temp = TOUCH_Get_Val();
        if (temp > res)
        {
            res = temp;
        }
    }
    return res;
}

#define TOUCH_GATE_VAL 100

u8 TOUCH_KEY_Scan(u8 mode)
{
    u8 sample = 3;
    u16 rval = 0;
    static u8 keyen = 0;
    u8 res = 0;

    if (mode == 1)
    {
        keyen = 0;
        sample = 6;
    }

    rval = TOUCH_Get_MaxVal(sample);
    if (rval > (touch_default_val + TOUCH_GATE_VAL) && (rval < (10 * touch_default_val)))
    {
        if ((keyen == 0) && (rval > (touch_default_val + TOUCH_GATE_VAL)))
        {
            res = 1;
        }
        printf("rval: %d\r\n", rval);
        keyen = 3;
    }
    if (keyen)
    {
        keyen--;
    }
    return res;
}
