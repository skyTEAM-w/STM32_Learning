#ifndef __FLASH_H__
#define __FLASH_H__

#include "system.h"

// EN25X系列/Q系列芯片列表
// EN25Q80  ID  0XEF13
// EN25Q16  ID  0XEF14
// EN25Q32  ID  0XEF15
// EN25Q64  ID  0XEF16
// EN25Q128 ID  0XEF17
#define EN25Q80     0XEF13
#define EN25Q16     0XEF14
#define EN25Q32     0XEF15
// #define EN25Q64 	0XEF16
// #define EN25Q128	0XEF17
// #define EN25Q64 	0XC816
// #define EN25Q64 	0X1C16		//GD25QXX
// #define EN25Q64 	0X2016		//XM25QHXX
#define EN25Q64     0XC216 // MXIC
#define EN25Q128    0XC817

extern u16 EN25QXX_TYPE; // 定义EN25QXX芯片型号

#define EN25QXX_CS PBout(12) // EN25QXX的片选信号

// 指令表
#define EN25X_WriteEnable       0x06
#define EN25X_WriteDisable      0x04
#define EN25X_ReadStatusReg     0x05
#define EN25X_WriteStatusReg    0x01
#define EN25X_ReadData          0x03
#define EN25X_FastReadData      0x0B
#define EN25X_FastReadDual      0x3B
#define EN25X_PageProgram       0x02
#define EN25X_BlockErase        0xD8
#define EN25X_SectorErase       0x20
#define EN25X_ChipErase         0xC7
#define EN25X_PowerDown         0xB9
#define EN25X_ReleasePowerDown  0xAB
#define EN25X_DeviceID          0xAB
#define EN25X_ManufactDeviceID  0x90
#define EN25X_JedecDeviceID     0x9F

#define EN25X_CS_Port   GPIOB
#define EN25X_CS_Pin    GPIO_Pin_12
#define EN25X_RCC       RCC_APB2Periph_GPIOB

void EN25QXX_Init(void);
u16 EN25QXX_ReadID(void);
u8 EN25QXX_ReadSR(void);
void EN25QXX_WriteSR(u8 sr);
void EN25QXX_Write_Disable(void);
void EN25QXX_Write_Enable(void);
void EN25QXX_Read(u8 *pBuffer, u32 Address, u16 Number);
void EN25QXX_Write_Page(u8 *pBuffer, u32 Address, u16 Number);
void EN25QXX_Wait_Busy(void);
void EN25QXX_Write(u8 *pBuffer, u32 Address, u16 Number);
void EN25QXX_Erase_Sector(u32 Dst_Address);
void EN25QXX_Erase_Chip(void);
void EN25QXX_PowerDown(void);
void EN25QXX_WeakUp(void);

#endif
