#pragma once

namespace Banana
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define BANANA_KEY_SPACE           ::Banana::Key::Space
#define BANANA_KEY_APOSTROPHE      ::Banana::Key::Apostrophe    /* ' */
#define BANANA_KEY_COMMA           ::Banana::Key::Comma         /* , */
#define BANANA_KEY_MINUS           ::Banana::Key::Minus         /* - */
#define BANANA_KEY_PERIOD          ::Banana::Key::Period        /* . */
#define BANANA_KEY_SLASH           ::Banana::Key::Slash         /* / */
#define BANANA_KEY_0               ::Banana::Key::D0
#define BANANA_KEY_1               ::Banana::Key::D1
#define BANANA_KEY_2               ::Banana::Key::D2
#define BANANA_KEY_3               ::Banana::Key::D3
#define BANANA_KEY_4               ::Banana::Key::D4
#define BANANA_KEY_5               ::Banana::Key::D5
#define BANANA_KEY_6               ::Banana::Key::D6
#define BANANA_KEY_7               ::Banana::Key::D7
#define BANANA_KEY_8               ::Banana::Key::D8
#define BANANA_KEY_9               ::Banana::Key::D9
#define BANANA_KEY_SEMICOLON       ::Banana::Key::Semicolon     /* ; */
#define BANANA_KEY_EQUAL           ::Banana::Key::Equal         /* = */
#define BANANA_KEY_A               ::Banana::Key::A
#define BANANA_KEY_B               ::Banana::Key::B
#define BANANA_KEY_C               ::Banana::Key::C
#define BANANA_KEY_D               ::Banana::Key::D
#define BANANA_KEY_E               ::Banana::Key::E
#define BANANA_KEY_F               ::Banana::Key::F
#define BANANA_KEY_G               ::Banana::Key::G
#define BANANA_KEY_H               ::Banana::Key::H
#define BANANA_KEY_I               ::Banana::Key::I
#define BANANA_KEY_J               ::Banana::Key::J
#define BANANA_KEY_K               ::Banana::Key::K
#define BANANA_KEY_L               ::Banana::Key::L
#define BANANA_KEY_M               ::Banana::Key::M
#define BANANA_KEY_N               ::Banana::Key::N
#define BANANA_KEY_O               ::Banana::Key::O
#define BANANA_KEY_P               ::Banana::Key::P
#define BANANA_KEY_Q               ::Banana::Key::Q
#define BANANA_KEY_R               ::Banana::Key::R
#define BANANA_KEY_S               ::Banana::Key::S
#define BANANA_KEY_T               ::Banana::Key::T
#define BANANA_KEY_U               ::Banana::Key::U
#define BANANA_KEY_V               ::Banana::Key::V
#define BANANA_KEY_W               ::Banana::Key::W
#define BANANA_KEY_X               ::Banana::Key::X
#define BANANA_KEY_Y               ::Banana::Key::Y
#define BANANA_KEY_Z               ::Banana::Key::Z
#define BANANA_KEY_LEFT_BRACKET    ::Banana::Key::LeftBracket   /* [ */
#define BANANA_KEY_BACKSLASH       ::Banana::Key::Backslash     /* \ */
#define BANANA_KEY_RIGHT_BRACKET   ::Banana::Key::RightBracket  /* ] */
#define BANANA_KEY_GRAVE_ACCENT    ::Banana::Key::GraveAccent   /* ` */
#define BANANA_KEY_WORLD_1         ::Banana::Key::World1        /* non-US #1 */
#define BANANA_KEY_WORLD_2         ::Banana::Key::World2        /* non-US #2 */

/* Function keys */
#define BANANA_KEY_ESCAPE          ::Banana::Key::Escape
#define BANANA_KEY_ENTER           ::Banana::Key::Enter
#define BANANA_KEY_TAB             ::Banana::Key::Tab
#define BANANA_KEY_BACKSPACE       ::Banana::Key::Backspace
#define BANANA_KEY_INSERT          ::Banana::Key::Insert
#define BANANA_KEY_DELETE          ::Banana::Key::Delete
#define BANANA_KEY_RIGHT           ::Banana::Key::Right
#define BANANA_KEY_LEFT            ::Banana::Key::Left
#define BANANA_KEY_DOWN            ::Banana::Key::Down
#define BANANA_KEY_UP              ::Banana::Key::Up
#define BANANA_KEY_PAGE_UP         ::Banana::Key::PageUp
#define BANANA_KEY_PAGE_DOWN       ::Banana::Key::PageDown
#define BANANA_KEY_HOME            ::Banana::Key::Home
#define BANANA_KEY_END             ::Banana::Key::End
#define BANANA_KEY_CAPS_LOCK       ::Banana::Key::CapsLock
#define BANANA_KEY_SCROLL_LOCK     ::Banana::Key::ScrollLock
#define BANANA_KEY_NUM_LOCK        ::Banana::Key::NumLock
#define BANANA_KEY_PRINT_SCREEN    ::Banana::Key::PrintScreen
#define BANANA_KEY_PAUSE           ::Banana::Key::Pause
#define BANANA_KEY_F1              ::Banana::Key::F1
#define BANANA_KEY_F2              ::Banana::Key::F2
#define BANANA_KEY_F3              ::Banana::Key::F3
#define BANANA_KEY_F4              ::Banana::Key::F4
#define BANANA_KEY_F5              ::Banana::Key::F5
#define BANANA_KEY_F6              ::Banana::Key::F6
#define BANANA_KEY_F7              ::Banana::Key::F7
#define BANANA_KEY_F8              ::Banana::Key::F8
#define BANANA_KEY_F9              ::Banana::Key::F9
#define BANANA_KEY_F10             ::Banana::Key::F10
#define BANANA_KEY_F11             ::Banana::Key::F11
#define BANANA_KEY_F12             ::Banana::Key::F12
#define BANANA_KEY_F13             ::Banana::Key::F13
#define BANANA_KEY_F14             ::Banana::Key::F14
#define BANANA_KEY_F15             ::Banana::Key::F15
#define BANANA_KEY_F16             ::Banana::Key::F16
#define BANANA_KEY_F17             ::Banana::Key::F17
#define BANANA_KEY_F18             ::Banana::Key::F18
#define BANANA_KEY_F19             ::Banana::Key::F19
#define BANANA_KEY_F20             ::Banana::Key::F20
#define BANANA_KEY_F21             ::Banana::Key::F21
#define BANANA_KEY_F22             ::Banana::Key::F22
#define BANANA_KEY_F23             ::Banana::Key::F23
#define BANANA_KEY_F24             ::Banana::Key::F24
#define BANANA_KEY_F25             ::Banana::Key::F25

/* Keypad */
#define BANANA_KEY_KP_0            ::Banana::Key::KP0
#define BANANA_KEY_KP_1            ::Banana::Key::KP1
#define BANANA_KEY_KP_2            ::Banana::Key::KP2
#define BANANA_KEY_KP_3            ::Banana::Key::KP3
#define BANANA_KEY_KP_4            ::Banana::Key::KP4
#define BANANA_KEY_KP_5            ::Banana::Key::KP5
#define BANANA_KEY_KP_6            ::Banana::Key::KP6
#define BANANA_KEY_KP_7            ::Banana::Key::KP7
#define BANANA_KEY_KP_8            ::Banana::Key::KP8
#define BANANA_KEY_KP_9            ::Banana::Key::KP9
#define BANANA_KEY_KP_DECIMAL      ::Banana::Key::KPDecimal
#define BANANA_KEY_KP_DIVIDE       ::Banana::Key::KPDivide
#define BANANA_KEY_KP_MULTIPLY     ::Banana::Key::KPMultiply
#define BANANA_KEY_KP_SUBTRACT     ::Banana::Key::KPSubtract
#define BANANA_KEY_KP_ADD          ::Banana::Key::KPAdd
#define BANANA_KEY_KP_ENTER        ::Banana::Key::KPEnter
#define BANANA_KEY_KP_EQUAL        ::Banana::Key::KPEqual

#define BANANA_KEY_LEFT_SHIFT      ::Banana::Key::LeftShift
#define BANANA_KEY_LEFT_CONTROL    ::Banana::Key::LeftControl
#define BANANA_KEY_LEFT_ALT        ::Banana::Key::LeftAlt
#define BANANA_KEY_LEFT_SUPER      ::Banana::Key::LeftSuper
#define BANANA_KEY_RIGHT_SHIFT     ::Banana::Key::RightShift
#define BANANA_KEY_RIGHT_CONTROL   ::Banana::Key::RightControl
#define BANANA_KEY_RIGHT_ALT       ::Banana::Key::RightAlt
#define BANANA_KEY_RIGHT_SUPER     ::Banana::Key::RightSuper
#define BANANA_KEY_MENU            ::Banana::Key::Menu
