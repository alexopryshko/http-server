cmake_minimum_required(VERSION 2.8.4)
project(http_server)

set(CMAKE_EXE_LINKER_FLAGS "-levent")
set(CMAKE_CXX_FLAGS "-std=c++0x")


set(SOURCE_FILES main.cpp http/response_header.cpp http/response.cpp http/request_header.cpp server/thread_pool/event_factory.cpp server/thread_pool/thread_pool.cpp server/server.cpp file_system/file.cpp file_system/file_system.cpp)
set(HEADER_FILES http/utilities.h http/response_header.h http/response.h http/request_header.h http/constants.h server/thread_pool/event_factory.h server/thread_pool/thread_pool.h server/server.h file_system/file.h file_system/file_system.h)

add_executable(http_server ${SOURCE_FILES})