cmake_minimum_required(VERSION 4.0)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_definitions(-BANANA_PLATFORM_MAC)
add_definitions(-BANANA_BUILD_DLL)

add_library(BananaEngine SHARED
        src/Banana/Core.cc
        include/Banana/Core.h
        src/Banana/Application.cc
        include/Banana/Application.h
        include/Banana/Banana.h
        src/Banana/EntryPoint.cc
        include/Banana/EntryPoint.h)

# 设置公共头文件目录（暴露给依赖模块）
target_include_directories(BananaEngine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
