//
// Created by 周春阳 on 2025/8/25.
//

#ifndef BANANA_LAYERSTACK_H
#define BANANA_LAYERSTACK_H

#include "Banana/Core/bapch.h"
#include "Banana/Core/Layer.h"
#include "Banana/Core/Core.h"

#include <vector>

namespace Banana {
    class API_EXPORT LayerStack {
    public:
        LayerStack();

        ~LayerStack();

        void PushLayer(Layer *layer);

        void PushOverlay(Layer *overlay);

        void PopLayer(Layer *layer);

        void PopOverlay(Layer *overlay);

        std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer *>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer *> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };
}


#endif //BANANA_LAYERSTACK_H
