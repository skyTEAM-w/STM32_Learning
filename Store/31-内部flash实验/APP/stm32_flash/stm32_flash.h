#ifndef __STM32_FLASH_H__
#define __STM32_FLASH_H__

#include "system.h"

//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 512 	 //��ѡSTM32��FLASH������С(��λΪK)

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ

vu16 STM32_FLASH_ReadHalfWord(u32 faddr);
void STM32_FLASH_Write_NoCheck(u32 Address, u16 *pBuffer, u16 Number);
void STM32_FLASH_Read(u32 Address, u16 *pBuffer, u16 Number);
void STM32_FLASH_Write(u32 Address, u16 *pBuffer, u16 Number);

#endif
