#!/bin/bash

set -e

git clone https://github.com/STMicroelectronics/stm32f1xx_hal_driver.git ../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver

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
