//
// Created by 周春阳 on 2025/8/21.
//

#ifndef BANANA_WINDOW_H
#define BANANA_WINDOW_H

#include "bapch.h"

#include "Core.h"
#include "Banana/Events/Event.h"

namespace Banana {
    struct WindowProps {
        std::string Title;
        uint32_t Width, Height;

        WindowProps(const std::string &title = "Banana Engine", uint32_t width = 1600,
                    uint32_t height = 900) : Title(title), Width(width), Height(height) {
        }
    };

    class API_EXPORT Window {
    public:
        typedef std::function<void(Event &)> EventCallbackFn;

        virtual ~Window() {
        }

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;

        virtual uint32_t GetHeight() const = 0;

        virtual void SetEventCallBack(const EventCallbackFn &callback) = 0;

        virtual void SetVSync(bool enabled) = 0;

        virtual bool IsVSync() const = 0;

        virtual void *GetNativeWindow() const = 0;

        static Window *Create(const WindowProps &props = WindowProps());
    };
}

#endif //BANANA_WINDOW_H
