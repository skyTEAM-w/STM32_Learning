#ifndef __IIC_H__
#define __IIC_H__

#include "system.h"

#define IIC_SCL_Pin GPIO_Pin_6
#define IIC_SDA_Pin GPIO_Pin_7
#define IIC_SCL_Port    GPIOB
#define IIC_SDA_Port    GPIOB
#define IIC_SCL_RCC RCC_APB2Periph_GPIOB
#define IIC_SDA_RCC RCC_APB2Periph_GPIOB

#define IIC_SCL     PBout(6)
#define IIC_SDA     PBout(7)
#define IIC_READ    PBin(7)

void IIC_Init(void);

void IIC_Send_Byte(u8 Byte);
u8 IIC_Read_Byte(u8 Ack);
u8 IIC_ReadAck(void);
void IIC_SendAck(u8 AckBit);
void IIC_Start(void);
void IIC_Stop(void);

#endif
