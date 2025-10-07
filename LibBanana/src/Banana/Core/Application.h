//
// Created by 周春阳 on 2025/8/18.
//

#ifndef BANANA_APPLICATION_H
#define BANANA_APPLICATION_H

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Banana/Events/ApplicationEvent.h"
#include "Banana/ImGui/ImGuiLayer.h"
#include "Banana/Renderer/Buffer.h"
#include "Banana/Renderer/Shader.h"
#include "Banana/Renderer/VertexArray.h"
#include "Banana/Renderer/OrthographicCamera.h"
#include "Banana/Core/Timestep.h"

namespace Banana {
    class API_EXPORT Application {
    public:
        Application(const std::string &name = "Banana App");

        virtual ~Application();

        void Run();

        void OnEvent(Event &event);

        void PushLayer(Layer *layer);

        void PushOverlay(Layer *layer);

        inline Window &GetWindow() { return *m_Window; }

        void Close();

        inline static Application &Get() { return *s_Instance; }

    private:
        bool OnWindowClose(WindowCloseEvent &event);

        bool OnWindowResize(WindowResizeEvent &event);

    private:
        std::unique_ptr<Window> m_Window;

        bool m_IsRunning = true;
        bool m_Minimize = false;

        LayerStack m_LayerStack;
        ImGuiLayer *m_ImGuiLayer;

        float m_LastFrameTime = 0.0f;

    private:
        static Application *s_Instance;
    };
}


#endif //BANANA_APPLICATION_H
