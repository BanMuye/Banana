//
// Created by 周春阳 on 2025/9/9.
//

#ifndef BANANA_TEXTURE_H
#define BANANA_TEXTURE_H
#include <cstdint>
#include <string>

#include "Banana/Core/Core.h"

namespace Banana {
    class Texture {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;

        virtual uint32_t GetHeight() const = 0;

        virtual uint32_t GetRendererID() const = 0;

        virtual void SetData(void *data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual bool IsLoaded() const = 0;

        virtual bool operator==(const Texture &other) const = 0;
    };

    class Texture2D : public Texture {
    public:
        static Ref<Texture2D> Create(uint32_t width, uint32_t height);

        static Ref<Texture2D> Create(const std::string &path);
    };
}


#endif //BANANA_TEXTURE_H
