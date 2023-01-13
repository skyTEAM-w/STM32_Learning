#include "spi.h"

void SPI2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStrcuture;
    SPI_InitTypeDef SPI_InitStructure;

    RCC_APB2PeriphClockCmd(SPI2_Port_RCC, ENABLE);
    RCC_APB1PeriphClockCmd(SPI2_RCC, ENABLE);

    GPIO_InitStrcuture.GPIO_Pin = SPI2_SCK | SPI2_MISO | SPI2_MOSI;
    GPIO_InitStrcuture.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStrcuture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI2_Port, &GPIO_InitStrcuture);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);

    SPI_Cmd(SPI2, ENABLE);
}

void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    SPI2->CR1 &= 0xFFC7;
    SPI1->CR1 |= SPI_BaudRatePrescaler;
    SPI_Cmd(SPI2, ENABLE);
}

u8 SPI2_ReadWriteByte(u8 TxData)
{
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
    {
    };

    SPI_I2S_SendData(SPI2, TxData);

    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
    {
    }
    return SPI_I2S_ReceiveData(SPI2);
}
