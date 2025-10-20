//
// Created by cyzho on 2025/10/21.
//

#include "OpenGLUniformBuffer.h"
#include "glad/glad.h"

Banana::OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding) {
    glCreateBuffers(1, &m_RendererID);
    glNamedBufferData(m_RendererID, size, NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
}

Banana::OpenGLUniformBuffer::~OpenGLUniformBuffer() {
    glDeleteBuffers(1, &m_RendererID);
}

void Banana::OpenGLUniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset) {
    glNamedBufferSubData(m_RendererID, offset, size, data);
}
