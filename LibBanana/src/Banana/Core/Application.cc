//
// Created by 周春阳 on 2025/8/18.
//
#include <iostream>
#include "Application.h"

#include "Banana/Platform/MacOS/MacOSWindow.h"

namespace Banana {
    Application::Application() {
        m_Window = std::unique_ptr<Window>(MacOSWindow::Create());
    }

    Application::~Application() = default;

    void Application::Run() {
        while (m_IsRunning) {
            m_Window->OnUpdate();
        }
    }
}
