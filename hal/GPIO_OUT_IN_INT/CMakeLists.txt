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
set(CMAKE_PROJECT_NAME GPIO_OUT_IN_INT)

# Include toolchain file
include("../../thirdparty/STM32L4XX/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

add_executable(${CMAKE_PROJECT_NAME}
    src/main.c
    src/stm32l4xx_it.c
    src/stm32l4xx_hal_msp.c
    src/system_stm32l4xx.c
    src/sysmem.c
    src/syscalls.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_tim.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_tim_ex.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_rcc.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_rcc_ex.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_flash.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_flash_ex.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_flash_ramfunc.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_gpio.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_i2c.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_i2c_ex.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_dma.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_dma_ex.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_pwr.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_pwr_ex.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_cortex.c
   ../../thirdparty/STM32L4XX_HAL/Src/stm32l4xx_hal_exti.c
   ../../thirdparty/STM32L4XX/startup_stm32l452xx.s
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE SYSTEM
    inc
    ../../thirdparty/STM32L4XX_HAL/Inc
    ../../thirdparty/STM32L4XX_HAL/Inc/Legacy
    ../../thirdparty/cmsis-header-stm32/stm32l4xx/Include
    ../../thirdparty/CMSIS_5/CMSIS/Core/Include
    ../../thirdparty/CMSIS_5/CMSIS/Include
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE SYSTEM
        USE_HAL_DRIVER 
        STM32L452xx
    $<$<CONFIG:Debug>:DEBUG>
)

if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()