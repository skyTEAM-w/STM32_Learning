SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Program Files\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;C:\Program Files\Java\jdk-17.0.4\bin;C:\Users\WuChengpei\AppData\Local\Programs\Python\Python310\Scripts\;D:\MinGW\bin;D:\Matlab\runtime\win64;D:\Matlab\bin;D:\Matlab\polyspace\bin;D:\Program Files\Polyspace\R2021a\runtime\win64;D:\Program Files\Polyspace\R2021a\bin;D:\Program Files\Polyspace\R2021a\polyspace\bin;C:\Program Files\Git\cmd;C:\Program Files (x86)\dotnet\;C:\Program Files\MySQL\MySQL Shell 8.0\bin\;C:\Users\WuChengpei\AppData\Local\Programs\Python\Python310\Scripts\;C:\Users\WuChengpei\AppData\Local\Programs\Python\Python310\;C:\Users\WuChengpei\AppData\Local\Microsoft\WindowsApps;;C:\Users\WuChengpei\AppData\Local\Programs\Microsoft VS Code\bin;C:\Program Files\JetBrains\PyCharm 2022.1.4\bin;
SET CPU_TYPE=STM32F103RB
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=LEDTEST
SET CPU_CLOCK=0x007A1200
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\ledtest\startup_stm32f103xb._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_it.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_msp.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_gpio_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_tim.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_tim_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_rcc_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_dma.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_cortex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_pwr.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_flash.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_flash_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\stm32f1xx_hal_exti.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ledtest\system_stm32f1xx.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\LEDTEST\LEDTEST.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\LEDTEST\LEDTEST.axf" --i32combined --output ".\LEDTEST\LEDTEST.hex"
