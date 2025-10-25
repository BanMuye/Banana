cmake_minimum_required(VERSION 3.30.5)
project(Banana)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)


add_executable(BananaShake
        src/BananaShake.cc
        src/EditorLayer.h
        src/EditorLayer.cc
        src/Panels/SceneHierarchyPanel.cc
        src/Panels/SceneHierarchyPanel.h
        src/Panels/ContentBrowserPanel.cc
        src/Panels/ContentBrowserPanel.h
)
target_link_libraries(BananaShake PRIVATE
        spdlog::spdlog
        glfw
        glm::glm
        glad::glad
        imguizmo::imguizmo
        imgui::imgui
        EnTT::EnTT
        yaml-cpp::yaml-cpp
        box2d::box2d
        BananaEngine
)