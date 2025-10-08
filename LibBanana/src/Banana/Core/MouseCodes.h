#pragma once

namespace Banana
{
    typedef enum class MouseCode : uint16_t
    {
        // From glfw3.h
        Button0                = 0,
        Button1                = 1,
        Button2                = 2,
        Button3                = 3,
        Button4                = 4,
        Button5                = 5,
        Button6                = 6,
        Button7                = 7,

        ButtonLast             = Button7,
        ButtonLeft             = Button0,
        ButtonRight            = Button1,
        ButtonMiddle           = Button2
    } Mouse;
	
    inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
    {
        os << static_cast<int32_t>(mouseCode);
        return os;
    }
}

#define BANANA_MOUSE_BUTTON_0      ::Banana::Mouse::Button0
#define BANANA_MOUSE_BUTTON_1      ::Banana::Mouse::Button1
#define BANANA_MOUSE_BUTTON_2      ::Banana::Mouse::Button2
#define BANANA_MOUSE_BUTTON_3      ::Banana::Mouse::Button3
#define BANANA_MOUSE_BUTTON_4      ::Banana::Mouse::Button4
#define BANANA_MOUSE_BUTTON_5      ::Banana::Mouse::Button5
#define BANANA_MOUSE_BUTTON_6      ::Banana::Mouse::Button6
#define BANANA_MOUSE_BUTTON_7      ::Banana::Mouse::Button7
#define BANANA_MOUSE_BUTTON_LAST   ::Banana::Mouse::ButtonLast
#define BANANA_MOUSE_BUTTON_LEFT   ::Banana::Mouse::ButtonLeft
#define BANANA_MOUSE_BUTTON_RIGHT  ::Banana::Mouse::ButtonRight
#define BANANA_MOUSE_BUTTON_MIDDLE ::Banana::Mouse::ButtonMiddle
