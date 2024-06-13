#!/bin/bash

if [ ! -d "../thirdparty/STM32F103X_HAL" ]; then
    git clone https://github.com/STMicroelectronics/stm32f1xx_hal_driver.git ../thirdparty/STM32F103X_HAL
fi

if [ ! -d "../thirdparty/cmsis-header-stm32" ]; then
    git clone https://github.com/modm-io/cmsis-header-stm32.git ../thirdparty/cmsis-header-stm32
fi

if [ ! -d "../thirdparty/CMSIS_5" ]; then
    git clone https://github.com/ARM-software/CMSIS_5.git ../thirdparty/CMSIS_5
fi

if [ ! -d "../thirdparty/openocd" ]; then
    git clone https://github.com/STMicroelectronics/OpenOCD.git ../thirdparty/openocd
fi


exit 0
