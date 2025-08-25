//
// Created by 周春阳 on 2025/8/18.
//

#ifndef BANANA_APPLICATION_H
#define BANANA_APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "Banana/Events/ApplicationEvent.h"

namespace Banana {
    class API_EXPORT Application {
    public:
        Application();

        virtual ~Application();

        void Run();

        void OnEvent(Event &event);

    private:
        bool OnWindowClose(WindowCloseEvent &event);

        std::unique_ptr<Window> m_Window;
        bool m_IsRunning = true;
    };
}


#endif //BANANA_APPLICATION_H
