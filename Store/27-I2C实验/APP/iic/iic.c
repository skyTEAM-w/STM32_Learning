#include "iic.h"
#include "SysTick.h"

void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(IIC_SCL_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(IIC_SDA_RCC, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = IIC_SCL_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IIC_SCL_Port, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = IIC_SDA_Pin;
    GPIO_Init(IIC_SDA_Port, &GPIO_InitStructure);
    
    IIC_SCL = 1;
    IIC_SDA = 1;
}

void SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = IIC_SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IIC_SDA_Port, &GPIO_InitStructure);
}

void SDA_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = IIC_SDA_Pin;
    GPIO_Init(IIC_SDA_Port, &GPIO_InitStructure);
}

void IIC_Start(void)
{
    SDA_OUT();
    IIC_SDA = 1;
    IIC_SCL = 1;
    delay_us(5);
    IIC_SDA = 0;
    delay_us(5);
    IIC_SCL = 0;
}

void IIC_Stop(void)
{
    SDA_OUT();
    IIC_SCL = 0;
    IIC_SDA = 0;
    IIC_SCL = 1;
    delay_us(5);
    IIC_SDA = 1;
    delay_us(5);
}

void IIC_SendAck(u8 AckBit)
{
    SDA_OUT();
    IIC_SCL = 0;
    IIC_SDA = AckBit;
    delay_us(2);
    IIC_SCL = 1;
    delay_us(5);
    IIC_SCL = 0;
}

u8 IIC_ReadAck(void)
{
    u8 tempTime = 0;
    IIC_SDA = 1;
    delay_us(1);
    SDA_IN();
    IIC_SCL = 1;
    delay_us(1);
    
    while (IIC_READ)
    {
        tempTime++;
        if (tempTime > 250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL = 0;
    return 0;
}

void IIC_Send_Byte(u8 Byte)
{
    u8 i = 0;
    for (i = 0; i < 8; i++)
    {
        IIC_SDA = Byte & (0x80 >> i);
        delay_us(2);
        IIC_SCL = 1;
        delay_us(2);
        IIC_SCL = 0;
        delay_us(2);
    }
}

u8 IIC_Read_Byte(u8 Ack)
{
    u8 i = 0, Byte = 0x00;
    
    SDA_IN();
    
    for (i = 0; i < 8; i++)
    {
        IIC_SCL = 0;
        delay_us(2);
        IIC_SCL = 1;
        delay_us(2);
        if (IIC_SDA)
        {
            Byte |= (0x80 >> i);
        }
        delay_us(2);
        IIC_SCL = 0;
    }
    
    IIC_SendAck(Ack);
    
    return Byte;
}
