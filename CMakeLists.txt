cmake_minimum_required(VERSION 2.8.4)
project(http_server)

set(CMAKE_EXE_LINKER_FLAGS    "-levent")

set(SOURCE_FILES main.cpp)
add_executable(http_server ${SOURCE_FILES})