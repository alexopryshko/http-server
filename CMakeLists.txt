cmake_minimum_required(VERSION 2.8.4)
project(http_server)

set(CMAKE_EXE_LINKER_FLAGS "-levent")
set(CMAKE_CXX_FLAGS "-std=c++0x")


set(SOURCE_FILES main.cpp http/ResponseHeader.cpp http/Response.cpp http/RequestHeader.cpp)
set(HEADER_FILES http/Utilities.h http/ResponseHeader.h http/Response.h http/RequestHeader.h)

add_executable(http_server ${SOURCE_FILES})