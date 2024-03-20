cmake_minimum_required(VERSION 3.6)
project(mylibrary_project)

include_directories(${CMAKE_SOURCE_DIR}/../lib)

add_executable(executable main.c)
target_link_libraries(executable ${CMAKE_SOURCE_DIR}/../lib/libmylibrary.so)
