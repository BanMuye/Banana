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

    BANANA_CORE_INFO("OpenGL Info:");
    BANANA_CORE_INFO("  Vendor: {0}", static_cast<const void*>(glGetString(GL_VENDOR)));
    BANANA_CORE_INFO("  Renderer: {0}", static_cast<const void*>(glGetString(GL_RENDERER)));
    BANANA_CORE_INFO("  Version: {0}", static_cast<const void*>(glGetString(GL_VERSION)));
}

void Banana::OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}
