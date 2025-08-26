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

        virtual void OnImGuiRender() override;

        void Begin();

        void End();

    private:
        float m_Time = 0.0f;
    };
}


#endif //BANANA_IMGUILAYER_H
