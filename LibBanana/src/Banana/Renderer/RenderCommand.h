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

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            s_RendererAPI->SetViewport(x, y, width, height);
        }

        inline static void SetClearColor(const glm::vec4 &color) {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear() {
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t count = 0) {
            s_RendererAPI->DrawIndexed(vertexArray, count);
        }

        inline static void DrawLines(const Ref<VertexArray> &vertexArray, uint32_t vertexCount) {
            s_RendererAPI->DrawLines(vertexArray, vertexCount);
        }

        inline static void SetLineWidth(float width) {
            s_RendererAPI->SetLineWidth(width);
        }

    private:
        static RendererAPI *s_RendererAPI;
    };
}


#endif //BANANA_RENDERCOMMAND_H
