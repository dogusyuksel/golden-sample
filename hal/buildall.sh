#!/bin/bash

set -e

git clone https://github.com/STMicroelectronics/stm32f1xx_hal_driver.git ../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver
git clone https://github.com/modm-io/cmsis-header-stm32.git ../thirdparty/STM32F1XX/Drivers/cmsis-header-stm32
git clone https://github.com/ARM-software/CMSIS_5.git ../thirdparty/STM32F1XX/Drivers/CMSIS_5
git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git ../thirdparty/FreeRTOS

files=$(find . -name '*' -type d -maxdepth 1 -mindepth 1)
while IFS= read -r line; do
    dirname=$(basename "$line")
    mkdir  $dirname/build
    cmake $dirname/ -B $dirname/build/
    make -C $dirname/build clean
    make -C $dirname/build all
    cd ..
done <<< "$files"

exit 0
