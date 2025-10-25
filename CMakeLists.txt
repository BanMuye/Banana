cmake_minimum_required(VERSION 3.30.5)


project(Banana)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)


find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(imguizmo CONFIG REQUIRED)
find_package(entt CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

add_subdirectory(LibBanana)
add_subdirectory(BananaShake)