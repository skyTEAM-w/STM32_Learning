#include "stm32_flash.h"

/**
 * @brief ��ȡָ����ַ����
 *
 * @param faddr ��ȡ��ַ
 * @return vu16 ��Ӧ����
 */
vu16 STM32_FLASH_ReadHalfWord(u32 faddr)
{
    return *(vu16 *)faddr;
}

/**
 * @brief �ڲ�flash�����д��
 *
 * @param Address ��ʼ��ַ
 * @param pBuffer ����ָ��
 * @param Number ����(16bits)��
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
 * @brief д��ָ����������
 * 
 * @param Address ��ʼ��ַ
 * @param pBuffer ����ָ��
 * @param Number ������
 */
void STM32_FLASH_Write(u32 Address, u16 *pBuffer, u16 Number)
{
    u32 secpos;    // ������ַ
    u16 secoff;    // ������ƫ��
    u16 secremain; // ����ʣ��
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
 * @brief ������
 *
 * @param Address ��ʼ��ַ
 * @param pBuffer �洢��
 * @param Number ������
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
