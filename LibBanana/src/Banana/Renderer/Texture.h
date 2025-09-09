//
// Created by 周春阳 on 2025/9/9.
//

#ifndef BANANA_TEXTURE_H
#define BANANA_TEXTURE_H
#include <cstdint>

#include "Banana/Core/Core.h"

namespace Banana {
    class Texture {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;

        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture {
    public:
        static Texture2D* Create(const std::string &path);
    };
}


#endif //BANANA_TEXTURE_H
