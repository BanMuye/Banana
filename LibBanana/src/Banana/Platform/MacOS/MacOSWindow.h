//
// Created by 周春阳 on 2025/8/21.
//

#ifndef BANANA_MACOSWINDOW_H
#define BANANA_MACOSWINDOW_H

#include "Banana/Core/bapch.h"

#include "Banana/Core/Window.h"
#include "GLFW/glfw3.h"

namespace Banana {
    class MacOSWindow : public Window {

    public:
        MacOSWindow(const WindowProps &props);

        virtual ~MacOSWindow() override;

        void OnUpdate() override;

        unsigned GetWidth() const override { return m_WindowData.Width; };

        unsigned GetHeight() const override { return m_WindowData.Height; };

        void SetEventCallBack(const EventCallbackFn &callback) override {m_WindowData.EventCallBack = callback;}

        void SetVSync(bool enabled) override;

        bool IsVSync() const override;

    private:
        virtual void Init(const WindowProps &props);

        virtual void Shutdown();

    private:
        GLFWwindow *m_Window;

        struct WindowData {
            std::string Title;
            unsigned Width, Height;
            unsigned VSync;

            EventCallbackFn EventCallBack;
        };

        WindowData m_WindowData;
    };
}


#endif //BANANA_MACOSWINDOW_H
