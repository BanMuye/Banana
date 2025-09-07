cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 11)

add_definitions(-BANANA_PLATFORM_MAC)

add_executable(SandboxApp
        src/SandboxApp.cc)

add_library(SandboxLib STATIC src/SandboxApp.cc)

target_link_libraries(SandboxApp PRIVATE BananaEngine)
