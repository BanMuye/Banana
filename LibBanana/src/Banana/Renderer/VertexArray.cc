//
// Created by 周春阳 on 2025/9/7.
//

#include "Banana/Core/bapch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Banana/Platform/OpenGL/OpenGLVertexArray.h"

namespace Banana {
    Ref<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: BANANA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return std::dynamic_pointer_cast<VertexArray>(
                    std::make_shared<OpenGLVertexArray>());
            default:
                BANANA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
        }
    }
}
