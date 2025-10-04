//
// Created by 周春阳 on 2025/9/9.
//

#ifndef BANANA_OPENGLTEXTURE_H
#define BANANA_OPENGLTEXTURE_H
#include <string>

#include "glad/glad.h"
#include "Banana/Renderer/Texture.h"

namespace Banana {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string &path);

        OpenGLTexture2D(uint32_t width, uint32_t height);

        virtual ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override;

        virtual uint32_t GetHeight() const override;

        virtual void SetData(void *data, uint32_t size) override;

        virtual void Bind(uint32_t slot = 0) const override;

        virtual bool operator==(const Texture &other) const override {
            if (auto p = dynamic_cast<const OpenGLTexture2D *>(&other)) {
                return m_RendererID == p->m_RendererID;
            }

            return false;
        }

    private:
        uint32_t m_Width;
        uint32_t m_Height;
        std::string m_Path;
        uint32_t m_RendererID;

        GLenum m_InternalFormat, m_DataFormat;
    };
}


#endif //BANANA_OPENGLTEXTURE_H
