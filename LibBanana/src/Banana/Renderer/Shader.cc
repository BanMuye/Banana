//
// Created by 周春阳 on 2025/9/7.
//

#include "Shader.h"

#include "glad/glad.h"
#include <vector>

#include "Renderer.h"
#include "Banana/Core/Assert.h"
#include "Banana/Core/Log.h"
#include "Banana/Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"

namespace Banana {
    Shader *Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: BANANA_CORE_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
            default: BANANA_CORE_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
        }
    }

    Shader *Shader::Create(const std::string &vertexFilePath, const std::string &fragmentFilePath,
                           const std::string &geometryFilePath) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: BANANA_CORE_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexFilePath, fragmentFilePath, geometryFilePath);
            default: BANANA_CORE_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
        }
    }
}
