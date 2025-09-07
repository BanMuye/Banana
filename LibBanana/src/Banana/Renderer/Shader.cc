//
// Created by 周春阳 on 2025/9/7.
//

#include "Shader.h"

#include "glad/glad.h"
#include <vector>

#include "Banana/Core/Assert.h"
#include "Banana/Core/Log.h"

Shader::Shader(const std::string &vertexSrc, const std::string &fragmentSrc) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vertexSrcData = vertexSrc.c_str();
    glShaderSource(vertexShader, 1, &vertexSrcData, 0);

    glCompileShader(vertexShader);
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(vertexShader);

        BANANA_CORE_INFO("{0}", infoLog.data());
        BANANA_CORE_ASSERT(false, "Vertex shader compilation failure!");
        return;
    }


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *fragmentSourceData = fragmentSrc.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourceData, 0);

    glCompileShader(fragmentShader);
    isCompiled = 0;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(fragmentShader);

        BANANA_CORE_INFO("{0}", infoLog.data());
        BANANA_CORE_ASSERT(false, "Fragment shader compilation failure!");
        return;
    }

    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertexShader);
    glAttachShader(m_RendererID, fragmentShader);
    glLinkProgram(m_RendererID);

    GLint isLinked = 0;
    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        BANANA_CORE_INFO("{0}", infoLog.data());
        BANANA_CORE_ASSERT(false, "Fragment shader compilation failure!");
        return;
    }
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() {
    glUseProgram(m_RendererID);
}

void Shader::UnBind() {
    glUseProgram(0);
}
