cmake_minimum_required(VERSION 2.8.4)
project(http_server)

set(CMAKE_EXE_LINKER_FLAGS "-levent")
set(CMAKE_CXX_FLAGS "-std=c++0x")


set(SOURCE_FILES main.cpp http/HTTPRequest.cpp)
set(HEADER_FILES http/HTTPRequest.h http/Utilities.h)

add_executable(http_server ${SOURCE_FILES})