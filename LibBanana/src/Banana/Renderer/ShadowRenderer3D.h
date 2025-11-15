//
// Created by cyzho on 2025/11/5.
//

#ifndef SHADOWRENDERER3D_H
#define SHADOWRENDERER3D_H
#include <glm/fwd.hpp>

#include "Framebuffer.h"
#include "Banana/Controller/LightController.h"


namespace Banana {
    class ShadowRenderer3D {
    public:
        static void Init();

        static void Shutdown();

        static void BeginScene(const LightController &lightController);

        static void EndScene();

        static void DrawCube(const glm::mat4 &transform);

    private:
        static void StartBatch();

        static void Flush();

        static void FlushAndReset();

        static void CalcLightSpaceViewProjection(const LightController &lightController);
    };
}


#endif //SHADOWRENDERER3D_H
