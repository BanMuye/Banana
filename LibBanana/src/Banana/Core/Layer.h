//
// Created by 周春阳 on 2025/8/25.
//

#ifndef BANANA_LAYER_H
#define BANANA_LAYER_H

#include "Banana/Core/bapch.h"
#include   "Banana/Core/Core.h"
#include "Banana/Events/Event.h"

namespace Banana {
    class Layer {
    public:
        Layer(const std::string &name = "Banana::Layer");

        virtual ~Layer() = default;

        virtual void OnAttach() {
        }

        virtual void OnDetach() {
        }

        virtual void OnUpdate() {
        }

        virtual void OnImGuiRender() {
        }

        virtual void OnEvent(Event &event) {
        }

        inline const std::string &GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };
}


#endif //BANANA_LAYER_H
