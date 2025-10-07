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
        static bool IsKeyPressed(int key);

        static bool IsMouseButtonPressed(int button);

        static std::pair<float, float> GetMousePosition();

        static float GetMouseX();

        static float GetMouseY();
    };
}

#endif //BANANA_INPUT_H
