//
// Created by 周春阳 on 2025/9/6.
//

#include "Banana/Core/bapch.h"
#include "glad/glad.h"
#include "OpenGLContext.h"

#include "Banana/Core/Assert.h"

Banana::OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle) {
    BANANA_CORE_ASSERT(windowHandle, "Window handle is null");
}

void Banana::OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    BANANA_CORE_ASSERT(status, "Failed to initialize");

    const GLubyte *versionStr = glGetString(GL_VERSION);
    const GLubyte *rendererStr = glGetString(GL_RENDERER);
    const GLubyte *vendorStr = glGetString(GL_VENDOR);
    const GLubyte *glslVersionStr = glGetString(GL_SHADING_LANGUAGE_VERSION);

    std::cout << "OpenGL 版本: " << versionStr << std::endl;
    std::cout << "渲染器: " << rendererStr << std::endl;
    std::cout << "供应商: " << vendorStr << std::endl;
    std::cout << "GLSL 版本: " << glslVersionStr << std::endl;
}

void Banana::OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}
