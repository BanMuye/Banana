cmake_minimum_required(VERSION 4.0)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_library(glad STATIC glad/src/glad.c glad/include/glad/glad.h glad/include/KHR/khrplatform.h)

target_include_directories(glad PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/glad/include>)