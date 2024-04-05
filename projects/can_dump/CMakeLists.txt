cmake_minimum_required(VERSION 3.1)
project(libcanard)

# Libcanard
include_directories(..)
include_directories(../drivers/socketcan)

# Compiler configuration - supporting only Clang and GCC
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -std=c99  -pedantic")

# C warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wdouble-promotion -Wswitch-enum -Wfloat-equal -Wundef")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wconversion -Wtype-limits")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wsign-conversion -Wcast-align -Wmissing-declarations -Wno-conversion -Wno-float-equal -Wno-double-promotion")

# Expose internal API for unit testing
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -DCANARD_INTERNAL=''")

add_executable(can_dumper
                can_dumper.c
               ../canard.c
               ../drivers/socketcan/socketcan.c)

target_compile_definitions(can_dumper
                         PUBLIC DEBUG_ENABLED=1)
