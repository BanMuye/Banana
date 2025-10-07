//
// Created by 周春阳 on 2025/8/26.
//

#ifndef BANANA_IMGUILAYER_H
#define BANANA_IMGUILAYER_H
#include "Banana/Core/Layer.h"

namespace Banana {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();

        ~ImGuiLayer();

        virtual void OnAttach() override;

        virtual void OnDetach() override;

        void Begin();

        void End();

        void OnEvent(Event &event) override;

        void BlockEvents(bool block) { m_BlockEvents = block; }

    private:
        bool m_BlockEvents = true;
        float m_Time = 0.0f;
    };
}


#endif //BANANA_IMGUILAYER_H
