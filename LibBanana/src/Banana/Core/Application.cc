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

    Application::Application(const std::string &name, ApplicationCommandLineArgs args) : m_CommonLineArgs(args) {
        BANANA_PROFILE_FUNCTION()
        BANANA_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(MacOSWindow::Create(name));
        m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {
        BANANA_PROFILE_FUNCTION();
    }

    void Application::Run() {
        while (m_IsRunning) {
            float time = (float) glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimize) {
                for (Layer *layer: m_LayerStack) {
                    layer->OnUpdate(timestep);
                }
            }

            m_ImGuiLayer->Begin();
            for (Layer *layer: m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &event) {
        BANANA_PROFILE_FUNCTION();
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(event);
            if (event.Handled)break;
        }
    }

    void Application::PushLayer(Layer *layer) {
        BANANA_PROFILE_FUNCTION();
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        BANANA_PROFILE_FUNCTION();
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Close() {
        m_IsRunning = false;
    }


    bool Application::OnWindowClose(WindowCloseEvent &event) {
        m_IsRunning = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &event) {
        if (event.GetWidth() == 0 || event.GetHeight() == 0) {
            m_Minimize = true;
            return false;
        }

        m_Minimize = false;
        Renderer::OnWindowResize(event.GetWidth() * 2, event.GetHeight() * 2);
        return false;
    }
}
