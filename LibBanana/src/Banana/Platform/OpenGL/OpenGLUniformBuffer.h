//
// Created by cyzho on 2025/10/21.
//

#ifndef OPENGLUNIFORMBUFFER_H
#define OPENGLUNIFORMBUFFER_H
#include "Banana/Renderer/UniformBuffer.h"


namespace Banana {
    class OpenGLUniformBuffer : public UniformBuffer {
    public:
        OpenGLUniformBuffer(uint32_t size, uint32_t binding);

        virtual ~OpenGLUniformBuffer();

        virtual void SetData(const void *data, uint32_t size, uint32_t offset) override;

    private:
        uint32_t m_RendererID;
    };
}


#endif //OPENGLUNIFORMBUFFER_H
