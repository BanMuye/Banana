//
// Created by 周春阳 on 2025/8/26.
//

#ifndef BANANA_MACOSINPUT_H
#define BANANA_MACOSINPUT_H

#include "Banana/Core/Input.h"
#include "Banana/Core/Core.h"


namespace Banana {
    class API_EXPORT MacOSInput : public Input {
    protected:
        bool IsKeyPressedImpl(int key) override;

        bool IsMouseButtonPressedImpl(int button) override;

        std::pair<float, float> GetMousePositionImpl() override;

        float GetMouseXImpl() override;

        float GetMouseYImpl() override;
    };
}

#endif //BANANA_MACOSINPUT_H
