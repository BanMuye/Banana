cmake_minimum_required(VERSION 3.30.5)
project(Banana)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)


set(CMAKE_CXX_STANDARD 20)

add_library(BananaEngine STATIC
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
        src/Banana/Core/OrthographicCameraController.h
        src/Banana/Renderer/Renderer2D.cc
        src/Banana/Renderer/Renderer2D.h
        src/Banana/Debug/Instrumentor.h
        src/Banana/Renderer/Framebuffer.cc
        src/Banana/Renderer/Framebuffer.h
        src/Banana/Platform/OpenGL/OpenGLFramebuffer.cc
        src/Banana/Platform/OpenGL/OpenGLFramebuffer.h
        src/Banana/Scene/Scene.cc
        src/Banana/Scene/Scene.h
        src/Banana/Scene/Component.h
        src/Banana/Scene/Entity.cc
        src/Banana/Scene/Entity.h
        src/Banana/Renderer/Camera.h
        src/Banana/Scene/ScriptableEntity.h
        src/Banana/Scene/SceneCamera.cc
        src/Banana/Scene/SceneCamera.h
        src/Banana/Scene/SceneSerializer.cc
        src/Banana/Scene/SceneSerializer.h
        src/Banana/Utils/PlatformUtils.h
        src/Banana/Platform/Windows/windowsPlatformUtils.cc
        src/Banana/Math/Math.cc
        src/Banana/Math/Math.h
        src/Banana/Renderer/EditorCamera.cc
        src/Banana/Renderer/EditorCamera.h
        src/Banana/Core/Timer.h
        src/Banana/Renderer/UniformBuffer.cc
        src/Banana/Renderer/UniformBuffer.h
        src/Banana/Platform/OpenGL/OpenGLUniformBuffer.cc
        src/Banana/Platform/OpenGL/OpenGLUniformBuffer.h
        src/Banana/Core/UUID.cc
        src/Banana/Core/UUID.h
        src/Banana/Renderer/Renderer3D.cc
        src/Banana/Renderer/Renderer3D.h
        src/Banana/Controller/LightController.cc
        src/Banana/Controller/LightController.h)

# 设置公共头文件目录（暴露给依赖模块）
target_include_directories(BananaEngine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)


target_link_libraries(BananaEngine PRIVATE
        spdlog::spdlog
        glfw
        glm::glm
        glad::glad
        imgui::imgui
        imguizmo::imguizmo
        EnTT::EnTT
        yaml-cpp::yaml-cpp
        box2d::box2d
)