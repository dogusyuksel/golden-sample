cmake_minimum_required(VERSION 3.6)
project(mylibrary_project)

# CMake instructions to make the static lib

add_library( mylibrary SHARED
		mylibrary.c )
