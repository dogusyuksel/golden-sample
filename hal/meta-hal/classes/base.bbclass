addtask build
addtask clean

SRC_URI =  "\
    file:///workspace/hal/base_example/src \
    file:///workspace/thirdparty/STM32L4XX_HAL/Src \
    file:///workspace/thirdparty/STM32L4A6ZGT \
    "

TOOLCHAIN_PATH = "/workspace/thirdparty/STM32L4A6ZGT/gcc-arm-none-eabi.cmake"

SOURCE_FILES_PATH = "/workspace/hal/base_example/src"
HAL_FILES_PATH = "/workspace/thirdparty/STM32L4XX_HAL/Src"
STARTUP_FILES_PATH = "/workspace/thirdparty/STM32L4A6ZGT"

INCLUDES_PATHS = "/workspace/hal/base_example/inc:/workspace/thirdparty/STM32L4XX_HAL/Inc:/workspace/thirdparty/STM32L4XX_HAL/Inc/Legacy:/workspace/thirdparty/CMSIS_5/CMSIS/Core/Include:/workspace/thirdparty/cmsis-header-stm32/stm32l4xx/Include"

do_apply_patch () {
    patch -d / -p0 --binary -N < ${PATCH_FILE}
}

do_revert_patch () {
    patch -d / -p0 --binary -R < ${PATCH_FILE}
}

do_build () {
    echo "Building..."
    cmake /workspace/hal/base_example \
     -DTOOLCHAIN_PATH=${TOOLCHAIN_PATH} \
     -DSOURCE_FILES_PATH=${SOURCE_FILES_PATH} \
     -DHAL_FILES_PATH=${HAL_FILES_PATH} \
     -DSTARTUP_FILES_PATH=${STARTUP_FILES_PATH} \
     -DINCLUDES_PATHS=${INCLUDES_PATHS} \
     -DNAME=${NAME} -DVER=${PV}
    make
    arm-none-eabi-objcopy -O binary bin/${NAME}-${PV}.elf bin/${NAME}-${PV}.bin
    echo "st-flash write ${NAME}-${PV}.bin 0x08000000" >> bin/flasher.sh
    chmod +x bin/flasher.sh
}

do_clean () {
    echo "Cleaning..."
    rm -rf bin
}

addtask do_apply_patch before do_build
addtask do_revert_patch before do_clean

EXPORT_FUNCTIONS do_build do_clean do_apply_patch do_revert_patch
