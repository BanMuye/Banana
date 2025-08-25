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

namespace Banana {
    class API_EXPORT Application {
    public:
        Application();

        virtual ~Application();

        void Run();

        void OnEvent(Event &event);

        void PushLayer(Layer *layer);

        void PushOverlay(Layer *layer);

    private:
        bool OnWindowClose(WindowCloseEvent &event);

        std::unique_ptr<Window> m_Window;
        bool m_IsRunning = true;
        LayerStack m_LayerStack;
    };
}


#endif //BANANA_APPLICATION_H
