//
// Created by 周春阳 on 2025/8/21.
//

#include "MacOSWindow.h"

#include "Banana/Core/Log.h"

namespace Banana {
    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char *description) {
        BANANA_CORE_ERROR("GLFW Error ({0}):{1}", error, description);
    }

    Window *Window::Create(const WindowProps &props) {
        return new MacOSWindow(props);
    }

    MacOSWindow::MacOSWindow(const WindowProps &props) {
        Init(props);
    }

    MacOSWindow::~MacOSWindow() {
        Shutdown();
    }

    void MacOSWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void MacOSWindow::SetEventCallBack(const EventCallbackFn &callback) {
    }

    void MacOSWindow::SetVSync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }

        m_WindowData.VSync = enabled;
    }

    bool MacOSWindow::IsVSync() const {
        return m_WindowData.VSync;
    }

    void MacOSWindow::Init(const WindowProps &props) {
        m_WindowData.Title = props.Title;
        m_WindowData.Width = props.Width;
        m_WindowData.Height = props.Height;

        BANANA_CORE_INFO("Creating window {0} {1} {2}", props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0) {
            int success = glfwInit();
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        {
            m_Window = glfwCreateWindow((int) props.Width, (int) props.Height, m_WindowData.Title.c_str(), nullptr,
                                        nullptr);
            ++s_GLFWWindowCount;
        }
    }

    void MacOSWindow::Shutdown() {
        glfwDestroyWindow(m_Window);
        if (s_GLFWWindowCount == 0) {
            glfwTerminate();
        }
    }
}
