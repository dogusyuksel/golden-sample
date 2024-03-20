cmake_minimum_required(VERSION 3.6)
project(mylibrary_project)

# CMake instructions to make the static lib

ADD_LIBRARY( mylibrary STATIC
		mylibrary.c )
