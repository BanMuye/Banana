//
// Created by cyzho on 2025/10/5.
//

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "Banana/Core/Core.h"
#include "glm/fwd.hpp"


namespace Banana {
    struct FramebufferSpecification {
        uint32_t Width, Height;
        uint32_t Sample = 1;

        bool SwapChainTarget = false;
    };

    class Framebuffer {
    public:
        virtual ~Framebuffer() = default;

        virtual void Bind() = 0;

        virtual void Unbind() = 0;

        virtual uint32_t GetColorAttachmentRendererID() const = 0;

        virtual const FramebufferSpecification &GetSpecification() const = 0;

        static Ref<Framebuffer> Create(const FramebufferSpecification &spec);
    };
}


#endif //FRAMEBUFFER_H
