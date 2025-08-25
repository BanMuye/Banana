cmake_minimum_required(VERSION 4.0)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_definitions(-BANANA_PLATFORM_MAC)
add_definitions(-BANANA_BUILD_DLL)
add_definitions(-BANANA_DEBUG_MODE)

add_library(BananaEngine SHARED
        src/Banana/Core/Core.h
        src/Banana/Core/Application.cc
        src/Banana/Core/Application.h
        src/Banana/Core/Banana.h
        src/Banana/Core/EntryPoint.cc
        src/Banana/Core/EntryPoint.h
        src/Banana/Core/Log.cc
        src/Banana/Core/Log.h
        src/Banana/Events/Event.h
        src/Banana/Events/KeyEvent.h
        src/Banana/Events/MouseEvent.h
        src/Banana/Events/ApplicationEvent.h
        src/Banana/Core/Base.h
        src/Banana/Core/KeyCodes.h
        src/Banana/Core/MouseCodes.h
        src/Banana/Core/bapch.h
        src/Banana/Core/Window.h
        src/Banana/Platform/MacOS/MacOSWindow.cc
        src/Banana/Platform/MacOS/MacOSWindow.h
        src/Banana/Core/Assert.h)

# 设置公共头文件目录（暴露给依赖模块）
target_include_directories(BananaEngine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

include(FetchContent)
FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.3
    GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(spdlog)
target_link_libraries(BananaEngine PUBLIC spdlog::spdlog)

FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.4
        GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(glfw)
target_link_libraries(BananaEngine PUBLIC glfw)



