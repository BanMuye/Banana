cmake_minimum_required(VERSION 3.30.5)
project(Banana)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(LibBanana)
add_subdirectory(Sandbox)
