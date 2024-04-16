cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME UART_ADC_DMA)

# Include toolchain file
include("../../thirdparty/STM32F1XX/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

file(GLOB free_rtos_all
     "../../thirdparty/FreeRTOS/*.c"
)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.c
    src/stm32f1xx_it.c
    src/stm32f1xx_hal_msp.c
    src/system_stm32f1xx.c
    src/sysmem.c
    src/syscalls.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    ../../thirdparty/STM32F1XX/startup_stm32f103xb.s
    ../../thirdparty/FreeRTOS/portable/GCC/ARM_CM3/port.c
    ../../thirdparty/FreeRTOS/portable/MemMang/heap_3.c
    ${free_rtos_all}
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE SYSTEM
    inc
    ../../thirdparty/STM32F1XX/Drivers/STM32F1xx_HAL_Driver/Inc
    ../../thirdparty/STM32F1XX/STM32F1xx_HAL_Driver/Inc/Legacy
    ../../thirdparty/STM32F1XX/CMSIS/Device/ST/STM32F1xx/Include
    ../../thirdparty/STM32F1XX/Drivers/cmsis-header-stm32/stm32f1xx/Include
    ../../thirdparty/STM32F1XX/Drivers/CMSIS_5/CMSIS/Core/Include
    ../../thirdparty/STM32F1XX/CMSIS_5/CMSIS/Include
    ../../thirdparty/FreeRTOS/include
    ../../thirdparty/FreeRTOS/portable/GCC/ARM_CM3
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE SYSTEM
	USE_HAL_DRIVER 
	STM32F103xB
    $<$<CONFIG:Debug>:DEBUG>
)


# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
