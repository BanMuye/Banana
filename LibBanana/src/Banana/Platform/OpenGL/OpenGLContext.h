//
// Created by 周春阳 on 2025/9/6.
//

#ifndef BANANA_OPENGLCONTEXT_H
#define BANANA_OPENGLCONTEXT_H

#include "Banana/Renderer/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Banana {
    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}

#endif