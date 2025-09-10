//
// Created by 周春阳 on 2025/9/8.
//

#ifndef BANANA_OPENGLSHADER_H
#define BANANA_OPENGLSHADER_H
#include "Banana/Renderer/Shader.h"

namespace Banana {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);

        // todo temp interface
;        OpenGLShader(const std::string &vertexFilePath, const std::string &fragmentFilePath,
                     const std::string &geometryFilePath);

        virtual ~OpenGLShader();

        virtual void Bind() const override;

        virtual void UnBind() const override;

        void UploadUniformInt(const std::string &name, int value);

        void UploadUniformFloat1(const std::string &name, float value);

        void UploadUniformFloat2(const std::string &name, glm::vec2 &value);

        void UploadUniformFloat3(const std::string &name, glm::vec3 &value);

        void UploadUniformFloat4(const std::string &name, glm::vec4 &value);

        void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);

        void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

    private:
        std::string ReadFromFilePath(const std::string &filepath);
        void Compile(const std::string &vertexSource, const std::string &fragmentSource, const std::string &geometrySource);
    private:
        uint32_t m_RendererID;
    };
}


#endif //BANANA_OPENGLSHADER_H
