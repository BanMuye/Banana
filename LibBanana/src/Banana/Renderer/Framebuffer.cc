//
// Created by cyzho on 2025/10/5.
//

#include "Banana/Core/bapch.h"
#include "Framebuffer.h"

#include "RendererAPI.h"
#include "Banana/Platform/OpenGL/OpenGLFramebuffer.h"

namespace Banana {
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification &spec) {
        switch (RendererAPI::GetAPI()) {
            case RendererAPI::API::None: BANANA_CORE_ASSERT(false, "RendererAPI::None is not supported");
                return nullptr;
            case RendererAPI::API::OpenGL: return std::dynamic_pointer_cast<Framebuffer>(
                    std::make_shared<OpenGLFramebuffer>(spec));
            default: BANANA_CORE_ASSERT(false, "Unknown RendererAPI");return nullptr;
        }
    }
}
