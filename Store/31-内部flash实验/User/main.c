#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "tftlcd.h"
#include "spi.h"
#include "flash.h"
#include "key.h"

const u8 text_buf[] = "STM32F103ZET6";
#define TEXT_LEN sizeof(text_buf)

int main()
{
    u8 i = 0;
    u8 key;
    u8 buffer[30];

    SysTick_Init(72);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
    USART1_Init(115200);
    KEY_Init();
    EN25QXX_Init();
    TFTLCD_Init();

    FRONT_COLOR = BLACK;
    LCD_ShowString(10, 10, tftlcd_data.width, tftlcd_data.height, 16, "STM32F103ZET6");
    LCD_ShowString(10, 50, tftlcd_data.width, tftlcd_data.height, 16, "FLASH-SPI Test");
    LCD_ShowString(10, 70, tftlcd_data.width, tftlcd_data.height, 16, "K_UP:Write   KEY1:Read");
    FRONT_COLOR = RED;

    while (EN25QXX_ReadID() != EN25Q128)
    {
        printf("Check Failed!\r\n");
        LCD_ShowString(10, 150, tftlcd_data.width, tftlcd_data.height, 16, "EN25Q128 Check Failed!  ");
        delay_ms(500);
    }

    printf("EN25Q128 Check Success!\r\n");
    LCD_ShowString(10, 150, tftlcd_data.width, tftlcd_data.height, 16, "EN25Q128 Check Success!");

    LCD_ShowString(10, 170, tftlcd_data.width, tftlcd_data.height, 16, "Write Data:");
    LCD_ShowString(10, 190, tftlcd_data.width, tftlcd_data.height, 16, "Read Data :");

    while (1)
    {
        key = KEY_Scan(0);
        if (key == KEY_UP_PRESS)
        {
            EN25QXX_Write((u8 *)text_buf, 0, TEXT_LEN);
            printf("Sended Data - %s\r\n", text_buf);
            LCD_ShowString(10 + 11 * 8, 170, tftlcd_data.width, tftlcd_data.height, 16, "STM32F103ZET6");
        }

        if (key == KEY1_PRESS)
        {
            EN25QXX_Read(buffer, 0, TEXT_LEN);
            printf("Received Data - %s\r\n", buffer);
            LCD_ShowString(10 + 11 * 8, 190, tftlcd_data.width, tftlcd_data.height, 16, buffer);
        }

        i++;
        if (i % 20 == 0)
        {
            LED1 = !LED1;
        }
        delay_ms(10);
    }
}
