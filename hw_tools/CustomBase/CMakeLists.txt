cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME CustomBase)

# Include toolchain file
include("../../thirdparty/STM32F103C8T/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

add_executable(${CMAKE_PROJECT_NAME}
    src/main.c
    src/stm32f1xx_it.c
    src/stm32f1xx_hal_msp.c
    src/stm32f1xx_hal_timebase_tim.c
    src/system_stm32f1xx.c
    src/sysmem.c
    src/syscalls.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_gpio_ex.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_adc.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_adc_ex.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_rcc.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_rcc_ex.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_gpio.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_dma.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_cortex.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_pwr.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_flash.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_flash_ex.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_exti.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_can.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_i2c.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_spi.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_tim.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_tim_ex.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_uart.c
    ../../thirdparty/STM32F103C8T/startup_stm32f103xb.s
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC SYSTEM
    inc
    ../../thirdparty/STM32F103X_HAL/Inc
    ../../thirdparty/STM32F103X_HAL/Inc/Legacy
    ../../thirdparty/cmsis-header-stm32/stm32f1xx/Include
    ../../thirdparty/CMSIS_5/CMSIS/Core/Include
    ../../thirdparty/CMSIS_5/CMSIS/Include
)


target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC SYSTEM
	USE_HAL_DRIVER 
	STM32F103xB
    $<$<CONFIG:Debug>:DEBUG>
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
