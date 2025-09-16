//
// Created by 周春阳 on 2025/8/21.
//

#include "glad/glad.h"
#include "MacOSWindow.h"

#include "Banana/Core/Assert.h"
#include "Banana/Core/Log.h"
#include "Banana/Events/ApplicationEvent.h"
#include "Banana/Events/KeyEvent.h"
#include "Banana/Events/MouseEvent.h"
#include "Banana/Platform/OpenGL/OpenGLContext.h"

namespace Banana {
    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char *description) {
        BANANA_CORE_ERROR("GLFW Error ({0}):{1}", error, description);
    }

    Window *Window::Create(const WindowProps &props) {
        return new MacOSWindow(props);
    }

    MacOSWindow::MacOSWindow(const WindowProps &props) {
        BANANA_PROFILE_FUNCTION();
        Init(props);
    }

    MacOSWindow::~MacOSWindow() {
        BANANA_PROFILE_FUNCTION();
        Shutdown();
    }

    void MacOSWindow::OnUpdate() {
        BANANA_PROFILE_FUNCTION();
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void MacOSWindow::SetVSync(bool enabled) {
        BANANA_PROFILE_FUNCTION();
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
        BANANA_PROFILE_FUNCTION();
        m_WindowData.Title = props.Title;
        m_WindowData.Width = props.Width;
        m_WindowData.Height = props.Height;

        BANANA_CORE_INFO("Creating window {0} {1} {2}", props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0) {
            int success = glfwInit();
            BANANA_CORE_ASSERT(success, "Could not initialize GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 使用Core Profile，VAO是必须的
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 针对macOS的附加设置
#endif
        m_Window = glfwCreateWindow((int) props.Width, (int) props.Height, m_WindowData.Title.c_str(), nullptr,
                                    nullptr);
        ++s_GLFWWindowCount;

        m_Context = new OpenGLContext(m_Window);
        m_Context->Init();
        glfwSetWindowUserPointer(m_Window, &m_WindowData);
        SetVSync(true);

        // set callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallBack(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallBack(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, false);
                    data.EventCallBack(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallBack(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, true);
                    data.EventCallBack(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallBack(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallBack(event);
                    break;;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float) xOffset, (float) yOffset);
            data.EventCallBack(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float) xPos, (float) yPos);
            data.EventCallBack(event);
        });
    }

    void MacOSWindow::Shutdown() {
        BANANA_PROFILE_FUNCTION();
        glfwDestroyWindow(m_Window);
        if (s_GLFWWindowCount == 0) {
            glfwTerminate();
        }
    }
}
