//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_RENDERER_H
#define BANANA_RENDERER_H

namespace Banana {
    enum class RendererAPI {
        None = 0, OpenGL = 1
    };

    class Renderer {
    public:
        inline static RendererAPI GetAPI() { return s_RendererAPI; }

    private:
        static RendererAPI s_RendererAPI;
    };
}


#endif //BANANA_RENDERER_H
