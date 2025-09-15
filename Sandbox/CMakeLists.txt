cmake_minimum_required(VERSION 4.0)

add_definitions(-BANANA_PLATFORM_MAC)

add_executable(SandboxApp
        src/SandboxApp.cc
        src/Sandbox2D.cc
        src/Sandbox2D.h)

add_library(SandboxLib STATIC src/SandboxApp.cc)

target_link_libraries(SandboxApp PRIVATE BananaEngine)
