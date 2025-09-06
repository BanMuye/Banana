//
// Created by 周春阳 on 2025/9/6.
//

#ifndef BANANA_GRAPHICSCONTEXT_H
#define BANANA_GRAPHICSCONTEXT_H

namespace Banana {
    class GraphicsContext {
    public:
        virtual void Init() = 0;

        virtual void SwapBuffers() = 0;
    };
}

#endif //BANANA_GRAPHICSCONTEXT_H