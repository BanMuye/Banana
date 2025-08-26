//
// Created by 周春阳 on 2025/8/26.
//

#ifndef BANANA_INPUT_H
#define BANANA_INPUT_H

#include "Banana/Core/bapch.h"
#include "Banana/Core/Core.h"

namespace Banana {
    class API_EXPORT Input {
    public:
        inline static bool IsKeyPressed(int key) { return s_Instance->IsKeyPressedImpl(key); }

        inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
        inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

    protected:
        virtual bool IsKeyPressedImpl(int key) =0;

        virtual bool IsMouseButtonPressedImpl(int button) =0;

        virtual std::pair<float, float> GetMousePositionImpl() =0;

        virtual float GetMouseXImpl() =0;

        virtual float GetMouseYImpl() =0;

    private:
        static Input *s_Instance;
    };
}

#endif //BANANA_INPUT_H
