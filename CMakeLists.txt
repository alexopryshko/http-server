cmake_minimum_required(VERSION 2.8.4)
project(http_server)

set(CMAKE_EXE_LINKER_FLAGS "-levent")
set(CMAKE_CXX_FLAGS "-std=c++0x")


set(SOURCE_FILES main.cpp http/response_header.cpp http/response.cpp http/request_header.cpp)
set(HEADER_FILES http/utilities.h http/response_header.h http/response.h http/request_header.h http/constants.h)

add_executable(http_server ${SOURCE_FILES})