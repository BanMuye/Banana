//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_RENDERCOMMAND_H
#define BANANA_RENDERCOMMAND_H

#include "RendererAPI.h"

namespace Banana {
    class RenderCommand {
    public:
        inline static void Init() {
            s_RendererAPI->Init();
        }

        inline static void SetClearColor(const glm::vec4 &color) {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear() {
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI *s_RendererAPI;
    };
}


#endif //BANANA_RENDERCOMMAND_H
