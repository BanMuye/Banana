//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_OPENGLBUFFER_H
#define BANANA_OPENGLBUFFER_H

#include "Banana/Renderer/Buffer.h"

namespace Banana {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float *vertices, uint32_t size);

        virtual ~OpenGLVertexBuffer() override;

        virtual void Bind() const override;

        virtual void UnBind() const override;

    private:
        uint32_t m_RendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t count);

        virtual ~OpenGLIndexBuffer() override;

        virtual void Bind() const override;

        virtual void UnBind() const override;

        virtual uint32_t GetCount() override { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}


#endif //BANANA_OPENGLBUFFER_H
