//
// Created by 周春阳 on 2025/9/7.
//

#include "Banana/Core/bapch.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"

namespace Banana {
    /** VertexBuffer */
    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {
        BANANA_PROFILE_FUNCTION();
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
        BANANA_PROFILE_FUNCTION();

        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        BANANA_PROFILE_FUNCTION();
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const {
        BANANA_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::UnBind() const {
        BANANA_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    const BufferLayout &OpenGLVertexBuffer::GetLayout() const {
        return m_Layout;
    }

    void OpenGLVertexBuffer::SetLayout(const BufferLayout &layout) {
        m_Layout = layout;
    }


    /** IndexBuffer */
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) {
        BANANA_PROFILE_FUNCTION();
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        this->m_Count = count;
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        BANANA_PROFILE_FUNCTION();
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const {
        BANANA_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::UnBind() const {
        BANANA_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetData(const void *data, uint32_t size) {
        BANANA_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
}
