//
// Created by 周春阳 on 2025/8/18.
//
#include <iostream>
#include "Banana/Renderer/Renderer.h"
#include "Application.h"


#include "Log.h"
#include "Banana/ImGui/ImGuiLayer.h"
#include "Banana/Platform/MacOS/MacOSWindow.h"
#include "Banana/Renderer/Buffer.h"
#include "GLFW//glfw3.h"

namespace Banana {
#define BIND_EVENT_FN(function) std::bind(&Application::function, this, std::placeholders::_1)

    Application *Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(MacOSWindow::Create());
        m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() = default;

    void Application::Run() {
        while (m_IsRunning) {

            float time = (float) glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (Layer *layer: m_LayerStack) {
                layer->OnUpdate(timestep);
            }

            m_ImGuiLayer->Begin();
            for (Layer *layer: m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        BANANA_CORE_TRACE("{0}", event.ToString());

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(event);
            if (event.Handled)break;
        }
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent &event) {
        m_IsRunning = false;
        return true;
    }
}
