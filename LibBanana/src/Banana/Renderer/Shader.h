//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_SHADER_H
#define BANANA_SHADER_H
#include <string>
#include <unordered_map>

#include "Banana/Core/Core.h"
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace Banana {
    class Shader {
    public:
        Shader() = default;

        virtual ~Shader() = default;

        virtual void Bind() const = 0;

        virtual void UnBind() const = 0;

        virtual void SetInt(const std::string &name, int value) = 0;

        virtual void SetFloat3(const std::string &name, const glm::vec3 &value) = 0;

        virtual void SetFloat4(const std::string &name, const glm::vec4 &value) =0;

        virtual void SetMat4(const std::string &name, const glm::mat4 &value) = 0;

        virtual std::string GetName() const = 0;

    public:
        static Ref<Shader> Create(const std::string &name, const std::string &vertexSrc,
                                  const std::string &fragmentSrc);

        static Ref<Shader> Create(const std::string &name, const std::string &vertexFilePath,
                                  const std::string &fragmentFilePath,
                                  const std::string &geometryFilePath);
    };

    class ShaderLibrary {
    public:
        void Add(const std::string &name, const Ref<Shader> &shader);

        void Add(const Ref<Shader> &shader);

        Ref<Shader> Load(const std::string &name, const std::string &vertexFilePath,
                         const std::string &fragmentFilePath, const std::string &geometryFilePath);

        Ref<Shader> Get(const std::string &name);

        bool Exists(const std::string &name);

    private:
        std::unordered_map<std::string, Ref<Shader> > m_Shaders;
    };
}

#endif //BANANA_SHADER_H
