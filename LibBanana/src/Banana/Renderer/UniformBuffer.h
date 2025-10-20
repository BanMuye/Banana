//
// Created by cyzho on 2025/10/21.
//

#ifndef UNIFORMBUFFER_H
#define UNIFORMBUFFER_H
#include <cstdint>

#include "Banana/Core/Core.h"


namespace Banana {
    class UniformBuffer {
    public:
        virtual ~UniformBuffer() {
        }

        virtual void SetData(const void *data, uint32_t size, uint32_t offset = 0) = 0;

        static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);
    };
}


#endif //UNIFORMBUFFER_H
