cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME CANBUS)

# Include toolchain file
include("../../thirdparty/STM32F103C8T/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

file(GLOB_RECURSE generated_files
     "generated_files/*.c"
)

file(GLOB free_rtos_all
     "../../thirdparty/FreeRTOS-Kernel/*.c"
)

file(GLOB src_all
     "src/*.c"
)

add_executable(${CMAKE_PROJECT_NAME}
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_gpio_ex.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_can.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_tim.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_tim_ex.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_uart.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_rcc.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_rcc_ex.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_gpio.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_dma.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_cortex.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_pwr.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_flash.c
    ../../thirdparty/STM32F103X_HAL/Src/stm32f1xx_hal_flash_ex.c
    ../../thirdparty/STM32F103C8T/startup_stm32f103xb.s
    ../../thirdparty/FreeRTOS-Kernel/portable/GCC/ARM_CM3/port.c
    ../../thirdparty/FreeRTOS-Kernel/portable/MemMang/heap_3.c
    libcanard/canard.c
    libcanard/drivers/stm32/canard_stm32.c
    ${free_rtos_all}
    ${src_all}
    ${generated_files}
)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC SYSTEM
    inc
    libcanard
    libcanard/drivers/stm32
    generated_files
    ../../thirdparty/STM32F103X_HAL/Inc
    ../../thirdparty/STM32F103X_HAL/Inc/Legacy
    ../../thirdparty/FreeRTOS-Kernel/portable/GCC/ARM_CM3
    ../../thirdparty/cmsis-header-stm32/stm32f1xx/Include
    ../../thirdparty/FreeRTOS-Kernel/include
    ../../thirdparty/CMSIS_5/CMSIS/Core/Include
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
