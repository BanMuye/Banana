//
// Created by 周春阳 on 2025/8/18.
//
#include <iostream>
#include "Application.h"

#include "Log.h"
#include "Banana/Platform/MacOS/MacOSWindow.h"

namespace Banana {
#define BIND_EVENT_FN(function) std::bind(&Application::function, this, std::placeholders::_1)

    Application::Application() {
        m_Window = std::unique_ptr<Window>(MacOSWindow::Create());
        m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application() = default;

    void Application::Run() {
        while (m_IsRunning) {
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        BANANA_CORE_TRACE("{0}", event.ToString());
    }

    bool Application::OnWindowClose(WindowCloseEvent &event) {
        m_IsRunning = false;
        return true;
    }
}
