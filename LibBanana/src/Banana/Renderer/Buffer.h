//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_BUFFER_H
#define BANANA_BUFFER_H
#include <cstdint>


namespace Banana {
    class VertexBuffer {
    public:
        virtual ~VertexBuffer() {
        }

        virtual void Bind() const = 0;

        virtual void UnBind() const = 0;

        static VertexBuffer *Create(float *vertices, uint32_t size);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() {
        }

        virtual void Bind() const = 0;

        virtual void UnBind() const = 0;

        virtual uint32_t GetCount() = 0;

        static IndexBuffer *Create(uint32_t *indices, uint32_t count);
    };
}


#endif //BANANA_BUFFER_H
