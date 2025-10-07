cmake_minimum_required(VERSION 3.30.5)

add_definitions(-BANANA_PLATFORM_MAC)

add_executable(BananaShake
        src/BananaShake.cc
        src/EditorLayer.h
        src/EditorLayer.cc
)

target_link_libraries(BananaShake PUBLIC BananaEngine)
