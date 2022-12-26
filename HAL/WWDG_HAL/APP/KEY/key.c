#include "key.h"

uint8_t KEY(uint8_t mode)
{
  static uint8_t key = 1;
  if (mode == 1)
    key = 1;
  if (key == 1 && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || KEY_UP == 1))
  {
    HAL_Delay(4);
    key = 0;
    if (KEY0 == 0)
    {
      return KEY0_PRESS;
    }
    else if (KEY1 == 0)
    {
      return KEY1_PRESS;
    }
    else if (KEY2 == 0)
    {
      return KEY2_PRESS;
    }
    else if (KEY_UP == 1)
    {
      return KEY_UP_PRESS;
    }
  }
  else if (key == 0 && (KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && KEY_UP == 0))
  {
    key = 1;
  }
  return 0;
}
