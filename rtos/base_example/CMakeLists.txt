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
set(CMAKE_PROJECT_NAME base_example)

# Include toolchain file
include("../../thirdparty/STM32L4A6ZGT/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

file(GLOB free_rtos_all
     "../../thirdparty/FreeRTOS-Kernel/*.c"
)

file(GLOB files_under_src
     "src/*.c"
)

file(GLOB files_under_hal
     "../../thirdparty/STM32L4XX_HAL/Src/*.c"
)

add_executable(${CMAKE_PROJECT_NAME}
    ${files_under_src}
    ${files_under_hal}
    ../../thirdparty/STM32L4A6ZGT/startup_stm32l4a6xx.s
    ../../thirdparty/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.c
    ../../thirdparty/FreeRTOS-Kernel/portable/MemMang/heap_3.c
    ${free_rtos_all}
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC SYSTEM
    inc
    ../../thirdparty/STM32L4XX_HAL/Inc
    ../../thirdparty/STM32L4XX_HAL/Inc/Legacy
    ../../thirdparty/cmsis-header-stm32/stm32l4xx/Include
    ../../thirdparty/CMSIS_5/CMSIS/Core/Include
    ../../thirdparty/CMSIS_5/CMSIS/Include
    ../../thirdparty/FreeRTOS-Kernel/include
    ../../thirdparty/FreeRTOS-Kernel/portable/GCC/ARM_CM4F
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC SYSTEM
	USE_HAL_DRIVER 
	STM32L4A6xx
    $<$<CONFIG:Debug>:DEBUG>
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
