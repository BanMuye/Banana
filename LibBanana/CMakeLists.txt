cmake_minimum_required(VERSION 4.0)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_definitions(-BANANA_PLATFORM_MAC)
add_definitions(-BANANA_BUILD_DLL)
add_definitions(-BANANA_DEBUG_MODE)

add_subdirectory(vendor)

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
        src/Banana/Core/Assert.h
        src/Banana/Core/Layer.cc
        src/Banana/Core/Layer.h
        src/Banana/Core/LayerStack.cc
        src/Banana/Core/LayerStack.h
        src/Banana/Core/Input.h
        src/Banana/Platform/MacOS/MacOSInput.h
        src/Banana/ImGui/ImGuiLayer.cc
        src/Banana/ImGui/ImGuiLayer.h
        src/Banana/Renderer/GraphicsContext.h
        src/Banana/Platform/OpenGL/OpenGLContext.cc
        src/Banana/Platform/OpenGL/OpenGLContext.h
        src/Banana/Renderer/Shader.cc
        src/Banana/Renderer/Shader.h
        src/Banana/Renderer/Buffer.cc
        src/Banana/Renderer/Buffer.h
        src/Banana/Renderer/Renderer.cc
        src/Banana/Renderer/Renderer.h
        src/Banana/Platform/OpenGL/OpenGLBuffer.cc
        src/Banana/Platform/OpenGL/OpenGLBuffer.h
        src/Banana/Renderer/VertexArray.cc
        src/Banana/Renderer/VertexArray.h
        src/Banana/Platform/OpenGL/OpenGLVertexArray.cc
        src/Banana/Platform/OpenGL/OpenGLVertexArray.h
        src/Banana/Renderer/RenderCommand.cc
        src/Banana/Renderer/RenderCommand.h
        src/Banana/Renderer/RendererAPI.cc
        src/Banana/Renderer/RendererAPI.h
        src/Banana/Platform/OpenGL/OpenGLRendererAPI.cc
        src/Banana/Platform/OpenGL/OpenGLRendererAPI.h
        src/Banana/Renderer/OrthographicCamera.cc
        src/Banana/Renderer/OrthographicCamera.h
        src/Banana/Core/Timestep.h
        src/Banana/Platform/MacOS/MacOSInput.cc
        src/Banana/Platform/OpenGL/OpenGLShader.cc
        src/Banana/Platform/OpenGL/OpenGLShader.h
        src/Banana/Renderer/Texture.cc
        src/Banana/Renderer/Texture.h
        src/Banana/Platform/OpenGL/OpenGLTexture.cc
        src/Banana/Platform/OpenGL/OpenGLTexture.h
        src/Banana/Core/MacroDefine.h
        src/Banana/Core/OrthographicCameraController.cc
        src/Banana/Core/OrthographicCameraController.h)

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

FetchContent_Declare(glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
        GIT_SHALLOW    glm)
FetchContent_MakeAvailable(glm)
target_link_libraries(BananaEngine PUBLIC glm)


target_link_libraries(BananaEngine PUBLIC glad)
target_link_libraries(BananaEngine PUBLIC imgui)
target_link_libraries(BananaEngine PUBLIC stb)
