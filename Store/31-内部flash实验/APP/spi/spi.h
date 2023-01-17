#ifndef __SPI_H__
#define __SPI_H__

#include "system.h"

#define SPI2_Port   GPIOB
#define SPI2_SCK    GPIO_Pin_13
#define SPI2_MISO   GPIO_Pin_14
#define SPI2_MOSI   GPIO_Pin_15
#define SPI2_RCC    RCC_APB1Periph_SPI2
#define SPI2_Port_RCC   RCC_APB2Periph_GPIOB

void SPI2_Init(void);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);
u8 SPI2_ReadWriteByte(u8 TxData);

#endif
