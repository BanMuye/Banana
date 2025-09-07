//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_RENDERER_H
#define BANANA_RENDERER_H

#include <Banana/Renderer/RenderCommand.h>

namespace Banana {
    class Renderer {
    public:
        static void BeginScene();

        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray> &vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}


#endif //BANANA_RENDERER_H
