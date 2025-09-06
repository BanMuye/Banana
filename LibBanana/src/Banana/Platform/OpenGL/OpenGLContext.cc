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
}

void Banana::OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}
