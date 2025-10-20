//
// Created by cyzho on 2025/10/21.
//

#include "Banana/Core/bapch.h"
#include "UniformBuffer.h"

#include "Renderer.h"
#include "Banana/Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Banana {
    Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: BANANA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLUniformBuffer>(size, binding);
            default: BANANA_CORE_ASSERT(false, "Unknown RendererAPI!");
                return nullptr;
        }
    }
}
