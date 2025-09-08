//
// Created by 周春阳 on 2025/8/21.
//

#ifndef BANANA_MOUSECODES_H
#define BANANA_MOUSECODES_H
#include <cstdint>

#define BANANA_MOUSE_BUTTON_1         0
#define BANANA_MOUSE_BUTTON_2         1
#define BANANA_MOUSE_BUTTON_3         2
#define BANANA_MOUSE_BUTTON_4         3
#define BANANA_MOUSE_BUTTON_5         4
#define BANANA_MOUSE_BUTTON_6         5
#define BANANA_MOUSE_BUTTON_7         6
#define BANANA_MOUSE_BUTTON_8         7
#define BANANA_MOUSE_BUTTON_LAST      BANANA_MOUSE_BUTTON_8
#define BANANA_MOUSE_BUTTON_LEFT      BANANA_MOUSE_BUTTON_1
#define BANANA_MOUSE_BUTTON_RIGHT     BANANA_MOUSE_BUTTON_2
#define BANANA_MOUSE_BUTTON_MIDDLE    BANANA_MOUSE_BUTTON_3

namespace Banana {
    typedef std::uint16_t MouseCode;

    namespace Mouse {
        enum : MouseCode {
            // todo @Banmuye to be finished by Banmuye 20250821
            unknown = 0,
        };
    }
}

#endif //BANANA_MOUSECODES_H
