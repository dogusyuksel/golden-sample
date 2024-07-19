#!/bin/bash

if [ ! -d "../thirdparty/STM32L4XX_HAL" ]; then
    git clone https://github.com/STMicroelectronics/stm32l4xx_hal_driver.git ../thirdparty/STM32L4XX_HAL
    files=$(find ../thirdparty/STM32L4XX_HAL -name '*template.c' -type f)
    while IFS= read -r line; do
        echo "deleted file $line"
        rm -rf $line
    done <<< "$files"
fi

if [ ! -d "../thirdparty/cmsis-header-stm32" ]; then
    git clone https://github.com/modm-io/cmsis-header-stm32.git ../thirdparty/cmsis-header-stm32
fi

if [ ! -d "../thirdparty/CMSIS_5" ]; then
    git clone https://github.com/ARM-software/CMSIS_5.git ../thirdparty/CMSIS_5
fi

if [ ! -d "../thirdparty/FreeRTOS-Kernel" ]; then
    git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git ../thirdparty/FreeRTOS-Kernel
fi

# if [ ! -d "../thirdparty/FreeRTOS" ]; then
#     git clone https://github.com/FreeRTOS/FreeRTOS.git ../thirdparty/FreeRTOS
# fi

if [ ! -d "../thirdparty/openocd" ]; then
    git clone https://github.com/STMicroelectronics/OpenOCD.git ../thirdparty/openocd
fi


exit 0
