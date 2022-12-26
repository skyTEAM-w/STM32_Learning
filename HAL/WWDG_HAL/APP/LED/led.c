#include "led.h"

void LD0_Turn_On(void)
{
  HAL_GPIO_WritePin(LD0_GPIO_Port, LD0_Pin, GPIO_PIN_RESET);
}
void LD0_Turn_Off(void)
{
  HAL_GPIO_WritePin(LD0_GPIO_Port, LD0_Pin, GPIO_PIN_SET);
}
void LD0_Toggle(void)
{
  HAL_GPIO_TogglePin(LD0_GPIO_Port, LD0_Pin);
}
void LD1_Turn_On(void)
{
  HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
}
void LD1_Turn_Off(void)
{
  HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
}
void LD1_Toggle(void)
{
  HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
}
