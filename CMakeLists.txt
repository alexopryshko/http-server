cmake_minimum_required(VERSION 2.8.4)
project(http_server)

set(CMAKE_EXE_LINKER_FLAGS "-levent")
set(CMAKE_CXX_FLAGS "-std=c++0x")


set(SOURCE_FILES main.cpp http/response_header.cpp http/request_header.cpp server/event_factory.cpp server/thread_pool.cpp server/server.cpp http/utility.cpp)
set(HEADER_FILES http/response_header.h http/request_header.h http/constants.h server/event_factory.h server/thread_pool.h server/server.h server/exception.h http/utility.h)

add_executable(http_server ${SOURCE_FILES})