//
// Created by 周春阳 on 2025/9/7.
//

#include "Banana/Core/bapch.h"
#include "Renderer.h"

namespace Banana {
    void Renderer::BeginScene() {
    }

    void Renderer::EndScene() {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray) {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}
