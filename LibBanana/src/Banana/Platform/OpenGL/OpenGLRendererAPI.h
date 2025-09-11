//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_OPENGLRENDERERAPI_H
#define BANANA_OPENGLRENDERERAPI_H

#include "Banana/Renderer/RendererAPI.h"

namespace Banana {
    class OpenGLRendererAPI : public RendererAPI {
    public:
        virtual void Init() override;

        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        virtual void SetClearColor(const glm::vec4 &color) override;

        virtual void Clear() override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
    };
}


#endif //BANANA_OPENGLRENDERERAPI_H
