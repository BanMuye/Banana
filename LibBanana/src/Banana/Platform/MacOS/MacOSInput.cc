//
// Created by 周春阳 on 2025/9/8.
//
#include "Banana/Core/bapch.h"
#include "Banana/Core/Application.h"
#include "Banana/Core/Input.h"
#include "Banana/Core/MouseCodes.h"
#include "GLFW/glfw3.h"

namespace Banana {
    bool Input::IsKeyPressed(KeyCode key) {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(MouseCode button) {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetMousePosition() {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return std::pair<float, float>(x, y);
    }

    float Input::GetMouseX() {
        auto [x, y] = GetMousePosition();
        return x;
    }

    float Input::GetMouseY() {
        auto [x, y] = GetMousePosition();
        return y;
    }
}
