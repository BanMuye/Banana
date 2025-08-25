//
// Created by 周春阳 on 2025/8/20.
//

#ifndef BANANA_KEYEVENT_H
#define BANANA_KEYEVENT_H
#include "Event.h"
#include "Banana/Core/KeyCodes.h"
#include "spdlog/sinks/basic_file_sink-inl.h"


namespace Banana {
    class KeyEvent : public Event {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategory::EventCategoryInput);

    protected:
        KeyEvent(const
            KeyCode keycode) : m_KeyCode(keycode) {
        }

        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(const int keycode, bool isRepeat = false) : KeyEvent(keycode), m_IsRepeat(isRepeat) {
        }

        bool IsRepeat() const { return m_IsRepeat; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (IsRepeat: " << m_IsRepeat << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        bool m_IsRepeat;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {
        }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {
        }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}


#endif //BANANA_KEYEVENT_H
