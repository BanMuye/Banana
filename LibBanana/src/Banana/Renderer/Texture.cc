//
// Created by 周春阳 on 2025/9/9.
//

#include "Texture.h"

#include "Renderer.h"
#include "Banana/Platform/OpenGL/OpenGLTexture.h"

namespace Banana {
    Texture2D *Texture2D::Create(const std::string &path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: BANANA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLTexture2D(path);
            default: BANANA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
        }
    }
}
