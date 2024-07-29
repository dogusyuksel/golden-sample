#!/bin/bash

if [ ! -d "../thirdparty/cmsis-header-stm32" ]; then
    git clone https://github.com/modm-io/cmsis-header-stm32.git ../thirdparty/cmsis-header-stm32
fi

if [ ! -d "../thirdparty/CMSIS_5" ]; then
    git clone https://github.com/ARM-software/CMSIS_5.git ../thirdparty/CMSIS_5
fi

if [ ! -d "../thirdparty/FreeRTOS-Kernel" ]; then
    git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git ../thirdparty/FreeRTOS-Kernel
fi

if [ ! -d "../thirdparty/openocd" ]; then
    git clone https://github.com/STMicroelectronics/OpenOCD.git ../thirdparty/openocd
fi

if [ ! -d "CANBUS/libcanard" ]; then
    git clone https://github.com/OpenCyphal/libcanard.git CANBUS/libcanard
    cd CANBUS/libcanard
    git checkout 43de1c4966b8d1e5d57978949d63e697f045b358
    git submodule update --init --recursive
    cd -
    patch -d CANBUS -p1 < ./CANBUS/transport.py.patch
    patch -d CANBUS -p1 < ./CANBUS/canard_stm32.patch
    ./CANBUS/libcanard/dsdl_compiler/libcanard_dsdlc ./CANBUS/nodes --incdir ./CANBUS/libcanard/dsdl_compiler/pyuavcan/uavcan --outdir ./CANBUS/generated_files
fi


exit 0
