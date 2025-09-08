//
// Created by 周春阳 on 2025/9/8.
//
#include "Banana/Core/bapch.h"
#include "Banana/Platform/MacOS/MacOSInput.h"
#include "Banana/Core/Application.h"
#include "GLFW/glfw3.h"

namespace Banana {
    Input *Input::s_Instance = new MacOSInput();

    bool MacOSInput::IsKeyPressedImpl(int key) {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool MacOSInput::IsMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> MacOSInput::GetMousePositionImpl() {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return std::pair<float, float>(x, y);
    }

    float MacOSInput::GetMouseXImpl() {
        auto [x, y] = GetMousePositionImpl();
        return x;
    }

    float MacOSInput::GetMouseYImpl() {
        auto [x, y] = GetMousePositionImpl();
        return y;
    }
}
