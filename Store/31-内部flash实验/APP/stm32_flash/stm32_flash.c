#include "stm32_flash.h"

/**
 * @brief 读取指定地址半字
 *
 * @param faddr 读取地址
 * @return vu16 对应数据
 */
vu16 STM32_FLASH_ReadHalfWord(u32 faddr)
{
    return *(vu16 *)faddr;
}

/**
 * @brief 内部flash不坚持写入
 *
 * @param Address 起始地址
 * @param pBuffer 数据指针
 * @param Number 半字(16bits)数
 */
void STM32_FLASH_Write_NoCheck(u32 Address, u16 *pBuffer, u16 Number)
{
    u16 i;
    for (i = 0; i < Number; i++)
    {
        FLASH_ProgramHalfWord(Address, pBuffer[i]);
        Address += 2;
    }
}

#if STM32_FLASH_SIZE < 256
#define STM32_SECTOR_SIZE 1024
#else
#define STM32_SECTOR_SIZE 2048
#endif

u16 STM32_FLASH_BUFFER[STM32_SECTOR_SIZE / 2];

/**
 * @brief 写入指定长度数据
 * 
 * @param Address 起始地址
 * @param pBuffer 数据指针
 * @param Number 半字数
 */
void STM32_FLASH_Write(u32 Address, u16 *pBuffer, u16 Number)
{
    u32 secpos;    // 扇区地址
    u16 secoff;    // 扇区内偏移
    u16 secremain; // 扇区剩余
    u16 i;
    u32 offaddr;

    if (Address < STM32_FLASH_BASE || (Address >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))
    {
        return;
    }

    FLASH_Unlock();

    offaddr = Address - STM32_FLASH_BASE;
    secpos = offaddr / STM32_SECTOR_SIZE;
    secoff = (offaddr % STM32_SECTOR_SIZE) / 2;
    secremain = STM32_SECTOR_SIZE / 2 - secoff;

    if (Number <= secremain)
    {
        secremain = Number;
    }

    while (1)
    {
        STM32_FLASH_Read(secpos * STM32_SECTOR_SIZE + STM32_FLASH_BASE, STM32_FLASH_BUFFER, STM32_SECTOR_SIZE);
        for (i = 0; i < secremain; i++)
        {
            if (STM32_FLASH_BUFFER[secoff + i] != 0xFFFF)
            {
                break;
            }
        }
        if (i < secremain)
        {
            FLASH_ErasePage(secpos * STM32_SECTOR_SIZE + STM32_FLASH_BASE);
            for (i = 0; i < secremain; i++)
            {
                STM32_FLASH_BUFFER[i + secoff] = pBuffer[i];
            }
            STM32_FLASH_Write_NoCheck(secpos * STM32_SECTOR_SIZE + STM32_FLASH_BASE, STM32_FLASH_BUFFER, STM32_SECTOR_SIZE / 2);
        }
        else
        {
            STM32_FLASH_Write_NoCheck(Address, pBuffer, secremain);
        }

        if (Number == secremain)
        {
            break;
        }
        else
        {
            secpos++;
            secoff = 0;
            pBuffer += secremain;
            Address += secremain;
            Number -= secremain;

            if (Number > (STM32_SECTOR_SIZE / 2))
            {
                secremain = STM32_SECTOR_SIZE / 2;
            }
            else
            {
                secremain = Number;
            }
        }
    }
    FLASH_Lock();
}

/**
 * @brief 读数据
 *
 * @param Address 起始地址
 * @param pBuffer 存储区
 * @param Number 半字数
 */
void STM32_FLASH_Read(u32 Address, u16 *pBuffer, u16 Number)
{
    u16 i;
    for (i = 0; i < Number; i++)
    {
        pBuffer[i] = STM32_FLASH_ReadHalfWord(Address);
        Address += 2;
    }
}
