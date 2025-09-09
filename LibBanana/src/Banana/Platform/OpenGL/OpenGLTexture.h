//
// Created by 周春阳 on 2025/9/9.
//

#ifndef BANANA_OPENGLTEXTURE_H
#define BANANA_OPENGLTEXTURE_H
#include <string>

#include "Banana/Renderer/Texture.h"

namespace Banana {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string &path);

        virtual ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override;

        virtual uint32_t GetHeight() const override;

        virtual void Bind(uint32_t slot = 0) const override;

    private:
        uint32_t m_Width;
        uint32_t m_Height;
        std::string m_Path;
        uint32_t m_RendererID;
    };
}


#endif //BANANA_OPENGLTEXTURE_H
