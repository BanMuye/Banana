//
// Created by 周春阳 on 2025/9/8.
//

#include "Banana/Core/bapch.h"
#include "Banana/Core/Core.h"
#include "glad/glad.h"
#include "OpenGLShader.h"

#include <fstream>

#include "glm/glm.hpp"

#include "Banana/Core/Assert.h"
#include "glm/gtc/type_ptr.inl"

namespace Banana {
    OpenGLShader::OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) {
        BANANA_PROFILE_FUNCTION();
        Compile(vertexSrc, fragmentSrc, std::string());
        m_Name = name;
    }

    OpenGLShader::OpenGLShader(const std::string &name, const std::string &vertexFilePath,
                               const std::string &fragmentFilePath,
                               const std::string &geometryFilePath) {
        BANANA_PROFILE_FUNCTION();
        std::string vertexSource = ReadFromFilePath(vertexFilePath);
        std::string fragmentSource = ReadFromFilePath(fragmentFilePath);
        std::string geometrySource = ReadFromFilePath(geometryFilePath);

        Compile(vertexSource, fragmentSource, geometryFilePath);

        m_Name = name;
    }

    OpenGLShader::~OpenGLShader() {
        BANANA_PROFILE_FUNCTION();
    }

    void OpenGLShader::Bind() const {
        BANANA_PROFILE_FUNCTION();
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::UnBind() const {
        BANANA_PROFILE_FUNCTION();
        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string &name, int value) {
        BANANA_PROFILE_FUNCTION();
        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &value) {
        BANANA_PROFILE_FUNCTION();
        UploadUniformFloat3(name, value);
    }

    void OpenGLShader::SetFloat4(const std::string &name, const glm::vec4 &value) {
        BANANA_PROFILE_FUNCTION();
        UploadUniformFloat4(name, value);
    }

    void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value) {
        BANANA_PROFILE_FUNCTION();
        UploadUniformMat4(name, value);
    }

    std::string OpenGLShader::GetName() const {
        return m_Name;
    }

    void OpenGLShader::UploadUniformInt(const std::string &name, int value) {
        BANANA_PROFILE_FUNCTION();
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformFloat1(const std::string &name, float value) {
        BANANA_PROFILE_FUNCTION();
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &value) {
        BANANA_PROFILE_FUNCTION();
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &value) {
        BANANA_PROFILE_FUNCTION();
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &value) {
        BANANA_PROFILE_FUNCTION();
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix) {
        BANANA_PROFILE_FUNCTION();
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) {
        BANANA_PROFILE_FUNCTION();
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    std::string OpenGLShader::ReadFromFilePath(const std::string &filepath) {
        BANANA_PROFILE_FUNCTION();
        std::string content;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (in) {
            in.seekg(0, std::ios::end);
            content.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&content[0], content.size());
            in.close();
        } else {
            BANANA_CORE_ERROR("Could not open file {}", filepath);
        }
        return content;
    }

    void OpenGLShader::Compile(const std::string &vertexSource, const std::string &fragmentSource,
                               const std::string &geometrySource) {
        BANANA_PROFILE_FUNCTION();
        GLuint program = glCreateProgram();

        // vertex
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar *vertexSourcePtr = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &vertexSourcePtr, 0);
        glCompileShader(vertexShader);
        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(vertexShader);
            BANANA_CORE_ERROR("{0}", infoLog.data());
            BANANA_CORE_ASSERT(false, "Vertex shader compilation failure!");
        }

        glAttachShader(program, vertexShader);

        // fragment
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar *fragmentSourcePtr = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &fragmentSourcePtr, 0);
        glCompileShader(fragmentShader);
        isCompiled = 0;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(fragmentShader);
            BANANA_CORE_ERROR("{0}", infoLog.data());
            BANANA_CORE_ASSERT(false, "fragment shader compilation failure!");
        }

        glAttachShader(program, fragmentShader);

        // geometry
        GLuint geometryShader = 0;
        if (!geometrySource.empty()) {
            geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
            const GLchar *geometrySourcePtr = geometrySource.c_str();
            glShaderSource(geometryShader, 1, &geometrySourcePtr, 0);
            glCompileShader(geometryShader);
            isCompiled = 0;
            glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &maxLength);
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(geometryShader, maxLength, &maxLength, &infoLog[0]);
                glDeleteShader(geometryShader);
                BANANA_CORE_ERROR("{0}", infoLog.data());
                BANANA_CORE_ASSERT(false, "geometry shader compilation failure!");
            }

            glAttachShader(program, geometryShader);
        }

        m_RendererID = program;

        glLinkProgram(program);
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            glDeleteProgram(program);
            BANANA_CORE_ERROR("{0}", infoLog.data());
            BANANA_CORE_ASSERT(false, "Program linking failure!");
            return;
        }

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);

        if (0 != geometryShader) {
            glDetachShader(program, geometryShader);
        }
    }
}
