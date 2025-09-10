//
// Created by 周春阳 on 2025/9/7.
//

#include "Renderer.h"

#include "Banana/Core/bapch.h"
#include "Renderer.h"

#include "Banana/Platform/OpenGL/OpenGLShader.h"

namespace Banana {
    Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData;

    void Renderer::Init() {
        RenderCommand::Init();
    }

    void Renderer::BeginScene(OrthographicCamera &camera) {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
    }

    void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray,
                          const glm::mat4 &transform) {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}
