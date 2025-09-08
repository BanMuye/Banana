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
        Shader() = default;

        virtual ~Shader() = default;

        virtual void Bind() const = 0;

        virtual void UnBind() const = 0;

    public:
        static Shader *Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}

#endif //BANANA_SHADER_H
