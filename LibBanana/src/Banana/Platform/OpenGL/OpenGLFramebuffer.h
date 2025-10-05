//
// Created by cyzho on 2025/10/5.
//

#ifndef OPENGLFRAMEBUFFER_H
#define OPENGLFRAMEBUFFER_H
#include "Banana/Renderer/Framebuffer.h"


namespace Banana {
    class OpenGLFramebuffer : public Framebuffer {
    public:
        OpenGLFramebuffer(const FramebufferSpecification &spec);

        virtual ~OpenGLFramebuffer() override;

        void Invalidate();

        virtual void Bind() override;

        virtual void Unbind() override;

        virtual uint32_t GetColorAttachmentRendererID() const override {
            return m_ColorAttachment;
        }

        virtual const FramebufferSpecification &GetSpecification() const override {
            return m_Specification;
        }

    private:
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment, m_DepthAttachment;
        FramebufferSpecification m_Specification;
    };
}


#endif //OPENGLFRAMEBUFFER_H
