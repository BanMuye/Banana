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
    Ref<Shader> Shader::Create(const std::string& name, const std::string &vertexSrc,
                               const std::string &fragmentSrc) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: BANANA_CORE_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return std::dynamic_pointer_cast<Shader>(
                    std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc));
            default: BANANA_CORE_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
        }
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string &vertexFilePath,
                               const std::string &fragmentFilePath,
                               const std::string &geometryFilePath) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: BANANA_CORE_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL: return std::dynamic_pointer_cast<Shader>(std::make_shared<OpenGLShader>(name,
                    vertexFilePath, fragmentFilePath, geometryFilePath));
            default: BANANA_CORE_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
        }
    }


    void ShaderLibrary::Add(const std::string &name, const Ref<Shader> &shader) {
        BANANA_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader> &shader) {
        auto name = shader->GetName();
        Add(name, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &name, const std::string &vertexFilePath,
                                    const std::string &fragmentFilePath, const std::string &geometryFilePath) {
        auto shader = Shader::Create(name, vertexFilePath, fragmentFilePath, geometryFilePath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string &name) {
        BANANA_CORE_ASSERT(Exists(name), "Shader not found!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string &name) {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}
