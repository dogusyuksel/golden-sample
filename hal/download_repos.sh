#!/bin/bash

if [ ! -d "../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver" ]; then
    git clone https://github.com/STMicroelectronics/stm32f1xx_hal_driver.git ../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver
fi

if [ ! -d "../thirdparty/STM32F1XX/Drivers/cmsis-header-stm32" ]; then
    git clone https://github.com/modm-io/cmsis-header-stm32.git ../thirdparty/STM32F1XX/Drivers/cmsis-header-stm32
fi

if [ ! -d "../thirdparty/STM32F1XX/Drivers/CMSIS_5" ]; then
    git clone https://github.com/ARM-software/CMSIS_5.git ../thirdparty/STM32F1XX/Drivers/CMSIS_5
fi

if [ ! -d "../thirdparty/FreeRTOS" ]; then
    git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git ../thirdparty/FreeRTOS
fi


if [ ! -d "../thirdparty/openocd" ]; then
    git clone https://github.com/STMicroelectronics/OpenOCD.git ../thirdparty/openocd
fi


exit 0
