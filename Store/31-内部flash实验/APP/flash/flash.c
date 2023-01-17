#include "flash.h"
#include "spi.h"
#include "SysTick.h"
#include "usart.h"

u16 EN25QXX_TYPE = EN25Q128;

/**
 * @brief EN25QXX��ʼ������
 *
 */

void EN25QXX_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(EN25X_RCC | RCC_APB2Periph_GPIOG, ENABLE);

    // FLASH CS PB12
    GPIO_InitStructure.GPIO_Pin = EN25X_CS_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(EN25X_CS_Port, &GPIO_InitStructure);
    GPIO_SetBits(EN25X_CS_Port, EN25X_CS_Pin);

    // NRF24L01 CS PG7
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    GPIO_SetBits(GPIOG, GPIO_Pin_7);

    EN25QXX_CS = 1;
    SPI2_Init();
    SPI2_SetSpeed(SPI_BaudRatePrescaler_2);
    EN25QXX_TYPE = EN25QXX_ReadID();
    printf("id of chip - %x\r\n", EN25QXX_TYPE);
}

/**
 * @brief ��ȡEN25QXXоƬID
 *
 * @return u16 ID��
 */
u16 EN25QXX_ReadID(void)
{
    u16 id = 0;
    EN25QXX_CS = 0;
    SPI2_ReadWriteByte(0x90);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    id |= SPI2_ReadWriteByte(0xFF) << 8;
    id |= SPI2_ReadWriteByte(0xFF);
    EN25QXX_CS = 1;
    return id;
}

/**
 * @brief ��ȡEN25QXX״̬�Ĵ���
 *
 * BIT7  6   5   4   3   2   1   0
 * SPR   RV  TB BP2 BP1 BP0 WEL BUSY
 * SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
 * TB,BP2,BP1,BP0:FLASH����д��������
 * WEL:дʹ������
 * BUSY:æ���λ(1,æ;0,����)
 *
 * @return u8 �Ĵ���״̬
 */
u8 EN25QXX_ReadSR(void)
{
    u8 byte = 0;
    EN25QXX_CS = 0;
    SPI2_ReadWriteByte(EN25X_ReadStatusReg);
    byte = SPI2_ReadWriteByte(0xFF);
    EN25QXX_CS = 1;
    return byte;
}

/**
 * @brief дW25QXXX״̬�Ĵ���
 *
 * @param sr �Ĵ���״̬
 */
void EN25QXX_WriteSR(u8 sr)
{
    EN25QXX_CS = 0;
    SPI2_ReadWriteByte(EN25X_WriteStatusReg);
    SPI2_ReadWriteByte(sr);
    EN25QXX_CS = 1;
}

/**
 * @brief EN25QXXдʹ��
 *
 */
void EN25QXX_Write_Enable(void)
{
    EN25QXX_CS = 0;
    SPI2_ReadWriteByte(EN25X_WriteEnable);
    EN25QXX_CS = 1;
}

/**
 * @brief EN25QXXд��ֹ
 *
 */
void EN25QXX_Write_Disable(void)
{
    EN25QXX_CS = 0;
    SPI2_ReadWriteByte(EN25X_WriteDisable);
    EN25QXX_CS = 1;
}
/**
 * @brief SPI FLASH��ȡ
 *
 * @param pBuffer ���ݴ洢��
 * @param Address ��ȡ��ַ(24bit)
 * @param Number ��ȡ�ֽ���(max:65535)
 */
void EN25QXX_Read(u8 *pBuffer, u32 Address, u16 Number)
{
    u16 i;
    EN25QXX_CS = 0;
    SPI2_ReadWriteByte(EN25X_ReadData);
    SPI2_ReadWriteByte((u8)((Address) >> 16));
    SPI2_ReadWriteByte((u8)((Address) >> 8));
    SPI2_ReadWriteByte((u8)Address);

    for (i = 0; i < Number; i++)
    {
        pBuffer[i] = SPI2_ReadWriteByte(0xFF);
    }

    EN25QXX_CS = 1;
}

/**
 * @brief EN25QXXҳ��д�ֽ�
 *
 * @param pBuffer ���ݴ洢��
 * @param Address д���ַ(24bits)
 * @param Number д���ֽ���(<256)
 */
void EN25QXX_Write_Page(u8 *pBuffer, u32 Address, u16 Number)
{
    u16 i;
    EN25QXX_Write_Enable();
    EN25QXX_CS = 0;
    SPI2_ReadWriteByte(EN25X_PageProgram);
    SPI2_ReadWriteByte((u8)((Address) >> 16));
    SPI2_ReadWriteByte((u8)((Address) >> 8));
    SPI2_ReadWriteByte((u8)Address);

    for (i = 0; i < Number; i++)
    {
        SPI2_ReadWriteByte(pBuffer[i]);
    }
    EN25QXX_CS = 1;
    EN25QXX_Wait_Busy();
}

/**
 * @brief �ȴ�����
 *
 */
void EN25QXX_Wait_Busy(void)
{
    while ((EN25QXX_ReadSR() & 0x01) == 0x01)
        ;
}

/**
 * @brief SPI_FLASH�޼���д
 *
 * @param pBuffer ���ݴ洢��
 * @param Address д���ַ(24bits)
 * @param Number д���ֽ���(max:65535)
 */
void EN25QXX_Write_NoCheck(u8 *pBuffer, u32 Address, u16 Number)
{
    u16 pageremain;
    pageremain = 256 - Address % 256;

    if (Number <= pageremain)
    {
        pageremain = Number;
    }

    while (1)
    {
        EN25QXX_Write_Page(pBuffer, Address, pageremain);
        if (Number == pageremain)
        {
            break;
        }
        else
        {
            pBuffer += pageremain;
            Address += pageremain;
            Number -= pageremain;
            if (Number > 256)
            {
                pageremain = 256;
            }
            else
            {
                pageremain = Number;
            }
        }
    }
}

// ���ݻ���
u8 EN25QXX_BUFFER[4096];

/**
 * @brief дSPI_FLASH
 *
 * @param pBuffer ���ݴ洢��
 * @param Address д��ַ(24bits)
 * @param Number �ֽ���(max:65535)
 */
void EN25QXX_Write(u8 *pBuffer, u32 Address, u16 Number)
{
    u32 secpos;
    u16 secoff;
    u16 secremain;
    u16 i;

    u8 *EN25QXX_BUF;
    EN25QXX_BUF = EN25QXX_BUFFER;
    secpos = Address / 4096;
    secoff = Address % 4096;
    secremain = 4096 - secoff;

    if (Number <= secremain)
    {
        secremain = Number;
    }

    while (1)
    {
        EN25QXX_Read(EN25QXX_BUF, secpos * 4096, 4096);

        for (i = 0; i < secremain; i++)
        {
            if (EN25QXX_BUF[secoff + i] != 0xFF)
            {
                break;
            }
        }

        if (i < secremain)
        {
            EN25QXX_Erase_Sector(secpos);
            for (i = 0; i < secremain; i++)
            {
                EN25QXX_BUF[secoff + i] = pBuffer[i];
            }
            EN25QXX_Write_NoCheck(pBuffer, Address, secremain);
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
                if (Number > 4096)
                {
                    secremain = 4096;
                }
                else
                {
                    secremain = Number;
                }
            }
        }
    }
}

/**
 * @brief ��������
 *
 * @param Dst_Address ������ַ
 */
void EN25QXX_Erase_Sector(u32 Dst_Address)
{
    printf("fe - %x\r\n", Dst_Address);
    Dst_Address *= 4096;
    EN25QXX_Write_Enable();
    EN25QXX_Wait_Busy();
    EN25QXX_CS = 0;
    SPI2_ReadWriteByte(EN25X_SectorErase);
    SPI2_ReadWriteByte((u8)((Dst_Address) >> 16));
    SPI2_ReadWriteByte((u8)((Dst_Address) >> 8));
    SPI2_ReadWriteByte((u8)Dst_Address);
    EN25QXX_CS = 1;
    EN25QXX_Wait_Busy();
}

/**
 * @brief ����оƬ
 * 
 */
void EN25QXX_Erase_Chip(void)
{
    EN25QXX_Write_Enable();
    EN25QXX_Wait_Busy();
    EN25QXX_CS = 0;
    SPI2_ReadWriteByte(EN25X_ChipErase);
    EN25QXX_CS = 1;
    EN25QXX_Wait_Busy();
}

/**
 * @brief оƬ����ģʽ
 * 
 */
void EN25QXX_PowerDown(void)
{
    EN25QXX_CS = 0;
    SPI2_ReadWriteByte(EN25X_PowerDown);
    EN25QXX_CS = 1;
    delay_us(3);
}

/**
 * @brief оƬ����
 * 
 */
void EN25QXX_WeakUp(void)
{
    EN25QXX_CS=0;
    SPI2_ReadWriteByte(EN25X_ReleasePowerDown);
    EN25QXX_CS=1;
    delay_us(3);
}
