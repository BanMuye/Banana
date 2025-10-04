//
// Created by 周春阳 on 2025/9/7.
//

#include "Buffer.h"

#include "Renderer.h"
#include "Banana/Core/Assert.h"
#include "Banana/Platform/OpenGL/OpenGLBuffer.h"

namespace Banana {
    Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: BANANA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return std::dynamic_pointer_cast<VertexBuffer>(
                    std::make_shared<OpenGLVertexBuffer>(vertices, size));
        }
        BANANA_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: BANANA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return std::dynamic_pointer_cast<VertexBuffer>(
                    std::make_shared<OpenGLVertexBuffer>(size));
        }
        BANANA_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: BANANA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return std::dynamic_pointer_cast<IndexBuffer>(
                    std::make_shared<OpenGLIndexBuffer>(indices, count));
        }
        BANANA_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
