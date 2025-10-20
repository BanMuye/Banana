//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_OPENGLVERTEXARRAY_H
#define BANANA_OPENGLVERTEXARRAY_H

#include "Banana/Renderer/VertexArray.h"

namespace Banana {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();

        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;

        virtual void UnBind() const override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;

        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer> > &GetVertexBuffers() const override;

        virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override;

    private :
        uint32_t m_RendererID;

        uint32_t m_VertexBufferIndex = 0;

        std::vector<std::shared_ptr<VertexBuffer> > m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}


#endif //BANANA_OPENGLVERTEXARRAY_H
