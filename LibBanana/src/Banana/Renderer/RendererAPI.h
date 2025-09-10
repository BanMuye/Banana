//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_RENDERERAPI_H
#define BANANA_RENDERERAPI_H
#include "VertexArray.h"
#include "glm/vec4.hpp"

namespace Banana {
    class RendererAPI {
    public:
        enum class API {
            None = 0, OpenGL = 1
        };

    public:
        virtual void Init() = 0;

        virtual void SetClearColor(const glm::vec4 &color) = 0;

        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) = 0;

        inline static API GetAPI() { return s_API; }

    private:
        static API s_API;
    };
}


#endif //BANANA_RENDERERAPI_H
