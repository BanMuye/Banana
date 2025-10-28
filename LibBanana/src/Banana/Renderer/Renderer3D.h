//
// Created by cyzho on 2025/10/28.
//

#ifndef RENDERER3D_H
#define RENDERER3D_H
#include "EditorCamera.h"


namespace Banana {
    class Renderer3D {
    public:
        static void Init();

        static void Shutdown();

        static void BeginScene(const EditorCamera &camera);

        static void BeginScene(const Camera &camera, glm::mat4 &transform);

        static void EndScene();

        static void DrawCube(const glm::mat4 &transform, const glm::vec4 &color, const int entityID);

        struct Statistics {
            uint32_t DrawCalls;
            uint32_t CubeCount;

            uint32_t GetTotalVertexCount() const { return CubeCount * 8; }
            uint32_t GetTotalIndexCount() const { return CubeCount * 6 * 6; }
        };

        static Statistics GetStats();

        static void ResetStats();

    private:
        static void StartBatch();

        static void Flush();

        static void FlushAndReset();

    };
}


#endif //RENDERER3D_H
