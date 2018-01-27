# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name

project(Allocator)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(".")