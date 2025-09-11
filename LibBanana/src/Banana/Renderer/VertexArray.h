//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_VERTEXARRAY_H
#define BANANA_VERTEXARRAY_H
#include <memory>

#include "Buffer.h"

namespace Banana {
    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;

        virtual void UnBind() const = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) = 0;

        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer> > &GetVertexBuffers() const = 0;

        virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const = 0;

        static Ref<VertexArray> Create();
    };
}


#endif //BANANA_VERTEXARRAY_H
