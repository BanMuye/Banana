//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_SHADER_H
#define BANANA_SHADER_H
#include <string>

#include "glm/fwd.hpp"

namespace Banana {
    class Shader {
    public:
        Shader(const std::string &vertexSrc, const std::string &fragmentSrc);

        ~Shader();

        void Bind();

        void UnBind();

        void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

    private:
        uint32_t m_RendererID;
    };
}

#endif //BANANA_SHADER_H
