#ifndef __STM32_FLASH_H__
#define __STM32_FLASH_H__

#include "system.h"

//用户根据自己的需要设置
#define STM32_FLASH_SIZE 512 	 //所选STM32的FLASH容量大小(单位为K)

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址

vu16 STM32_FLASH_ReadHalfWord(u32 faddr);
void STM32_FLASH_Write_NoCheck(u32 Address, u16 *pBuffer, u16 Number);
void STM32_FLASH_Read(u32 Address, u16 *pBuffer, u16 Number);
void STM32_FLASH_Write(u32 Address, u16 *pBuffer, u16 Number);

#endif
