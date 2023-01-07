#ifndef __24CXX_H__
#define __24CXX_H__

#include "system.h"
#include "iic.h"

#define AT24C01     127
#define AT24C02     255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767

#define TYPE        AT24C02

void AT24CXX_init(void);
u8 AT24CXX_Read_Byte(u16 WordAddress);
void AT24CXX_Write_Byte(u16 WordAddress, u8 Data);
void AT24CXX_Write_xByte(u16 WordAddress, u32 Data, u8 x);
u32 AT24CXX_Read_xData(u16 WordAddress, u8 x);
u8 AT24CXX_Check(void);
void AT24CXX_Read(u16 WordAddress, u8 *pBuffer, u16 Num);
void AT24CXX_Write(u16 WordAddress, u8 *pBuffer, u16 Num);

#endif
