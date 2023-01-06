#include "24cxx.h"
#include "SysTick.h"

void AT24CXX_init(void)
{
    IIC_Init();
}

u8 AT24CXX_Read_Byte(u16 WordAddress)
{
    u8 temp = 0;
    IIC_Start();
    
    if (TYPE > AT24C16)
    {
        IIC_Send_Byte(0xA0);
        IIC_ReadAck();
        IIC_Send_Byte(WordAddress >> 8);
    }
    else
    {
        IIC_Send_Byte(0xA0 + ((WordAddress / 256) << 1));
    }
    
    IIC_ReadAck();
    IIC_Send_Byte(WordAddress % 256);
    IIC_ReadAck();
    IIC_Start();
    IIC_Send_Byte(0xA1);
    IIC_ReadAck();
    temp = IIC_Read_Byte(0);
    IIC_Stop();
    
    return temp;
}

void AT24CXX_Write_Byte(u16 WordAddress, u8 Data)
{
    IIC_Start();
    
    if (TYPE > AT24C16)
    {
        IIC_Send_Byte(0xA0);
        IIC_ReadAck();
        IIC_Send_Byte(WordAddress >> 8);
    }
    else
    {
        IIC_Send_Byte(0xA0 + ((WordAddress / 256) << 1));
    }
    
    IIC_ReadAck();
    IIC_Send_Byte(WordAddress % 256);
    IIC_ReadAck();
    IIC_Send_Byte(Data);
    IIC_ReadAck();
    IIC_Stop();
    delay_ms(10);
}

void AT24CXX_Write_xByte(u16 WordAddress, u32 Data, u8 x)
{
    u8 i;
    
    for (i = 0; i < x; i++)
    {
        AT24CXX_Write_Byte(WordAddress + i, (Data >> (8 * i)) & 0xFF);
    }
}

u32 AT24CXX_Read_xData(u16 WordAddress, u8 x)
{
    u8 i;
    u32 Data = 0;
    
    for (i = 0; i < x; i++)
    {
        Data <<= 8;
        Data += AT24CXX_Read_Byte(WordAddress + x - i - 1);
    }
    return Data;
}

u8 AT24CXX_Check(void)
{
    u8 temp;
    temp = AT24CXX_Read_Byte(255);
    
    if (temp == 0x36)
    {
        return 0;
    }
    else
    {
        AT24CXX_Write_Byte(255, 0x36);
        temp = AT24CXX_Read_Byte(255);
        
        if (temp == 0x36)
        {
            return 0;
        }
    }
    
    return 1;
}

void AT24CXX_Read(u16 WordAddress, u8 *pBuffer, u16 Num)
{
    while (Num)
    {
        *pBuffer++ = AT24CXX_Read_Byte(WordAddress++);
        Num--;
    }
}

void AT24CXX_Write(u16 WordAddress, u8 *pBuffer, u16 Num)
{
    while (Num--)
    {
        AT24CXX_Write_Byte(WordAddress, *pBuffer);
        WordAddress++;
        pBuffer++;
    }
}
