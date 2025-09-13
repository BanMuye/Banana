//
// Created by 周春阳 on 2025/9/8.
//

#ifndef BANANA_OPENGLSHADER_H
#define BANANA_OPENGLSHADER_H
#include "Banana/Renderer/Shader.h"
#include "glm/fwd.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace Banana {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);

        OpenGLShader(const std::string &name, const std::string &vertexFilePath, const std::string &fragmentFilePath,
                     const std::string &geometryFilePath);

        virtual ~OpenGLShader();

        virtual void Bind() const override;

        virtual void UnBind() const override;

        virtual std::string GetName() const override;

        void UploadUniformInt(const std::string &name, int value);

        void UploadUniformFloat1(const std::string &name, float value);

        void UploadUniformFloat2(const std::string &name, const glm::vec2 &value);

        void UploadUniformFloat3(const std::string &name, const glm::vec3 &value);

        void UploadUniformFloat4(const std::string &name, const glm::vec4 &value);

        void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);

        void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

    private:
        std::string ReadFromFilePath(const std::string &filepath);

        void Compile(const std::string &vertexSource, const std::string &fragmentSource,
                     const std::string &geometrySource);

    private:
        uint32_t m_RendererID;
        std::string m_Name;
    };
}


#endif //BANANA_OPENGLSHADER_H
