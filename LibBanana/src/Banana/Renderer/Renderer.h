//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_RENDERER_H
#define BANANA_RENDERER_H

#include <Banana/Renderer/RenderCommand.h>

#include "Banana/Renderer/OrthographicCamera.h"
#include "Banana/Renderer/Shader.h"

namespace Banana {
    class Renderer {
    public:

        static void Init();

        static void BeginScene(OrthographicCamera &camera);

        static void EndScene();

        static void Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray,
                           const glm::mat4 &transform = glm::mat4(1.0f));

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData *s_SceneData;
    };
}


#endif //BANANA_RENDERER_H
