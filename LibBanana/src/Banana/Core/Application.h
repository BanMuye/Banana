//
// Created by 周春阳 on 2025/8/18.
//

#ifndef BANANA_APPLICATION_H
#define BANANA_APPLICATION_H

#include "Core.h"
#include "Window.h"

namespace Banana {
    class API_EXPORT Application {
    public:
        Application();

        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<Window> m_Window;
        bool m_IsRunning = true;
    };
}


#endif //BANANA_APPLICATION_H
