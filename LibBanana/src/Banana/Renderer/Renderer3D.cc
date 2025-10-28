//
// Created by cyzho on 2025/10/28.
//

#include "Banana/Core/bapch.h"
#include "Renderer3D.h"

#include "RenderCommand.h"
#include "Shader.h"
#include "UniformBuffer.h"
#include "VertexArray.h"

namespace Banana {
    struct CubeVertex {
        glm::vec3 Position;
        glm::vec4 Color;

        // Editor-only
        int EntityID;
    };

    struct Renderer3DData {
        static constexpr uint32_t MaxCube = 10000;
        static constexpr uint32_t MaxVertices = MaxCube * 8;
        static constexpr uint32_t MaxIndices = MaxCube * 6 * 6;

        Ref<VertexArray> CubeVertexArray;
        Ref<VertexBuffer> CubeVertexBuffer;

        Ref<Shader> CubeShader;

        uint32_t CubeIndexCount = 0;
        CubeVertex *CubeVertexBufferBase = nullptr;
        CubeVertex *CubeVertexBufferPtr = nullptr;

        glm::vec4 CubeVertexPositions[8]{};

        Renderer3D::Statistics Stats{};

        struct CameraData {
            glm::mat4 ViewProjection;
        };

        CameraData CameraBuffer{};
        Ref<UniformBuffer> CameraUniformBuffer;
    };

    static Renderer3DData s_Data;

    void Renderer3D::Init() {
        BANANA_PROFILE_FUNCTION();

        s_Data.CubeVertexArray = VertexArray::Create();
        s_Data.CubeVertexBuffer = VertexBuffer::Create(Renderer3DData::MaxVertices * sizeof(CubeVertex));
        s_Data.CubeVertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
            {ShaderDataType::Int, "a_EntityID"}
        });

        s_Data.CubeVertexArray->AddVertexBuffer(s_Data.CubeVertexBuffer);

        s_Data.CubeVertexBufferBase = new CubeVertex[Renderer3DData::MaxVertices];
        s_Data.CubeVertexBufferPtr = s_Data.CubeVertexBufferBase;

        uint32_t *cubeIndices = new uint32_t[Renderer3DData::MaxIndices];
        for (uint32_t i = 0; i < Renderer3DData::MaxIndices; i += 36) {
            cubeIndices[i] = 0;
            cubeIndices[i + 1] = 1;
            cubeIndices[i + 2] = 2;

            cubeIndices[i + 3] = 2;
            cubeIndices[i + 4] = 3;
            cubeIndices[i + 5] = 0;

            cubeIndices[i + 6] = 4;
            cubeIndices[i + 7] = 5;
            cubeIndices[i + 8] = 6;

            cubeIndices[i + 9] = 6;
            cubeIndices[i + 10] = 7;
            cubeIndices[i + 11] = 4;

            cubeIndices[i + 12] = 4;
            cubeIndices[i + 13] = 0;
            cubeIndices[i + 14] = 3;

            cubeIndices[i + 15] = 3;
            cubeIndices[i + 16] = 7;
            cubeIndices[i + 17] = 4;

            cubeIndices[i + 18] = 5;
            cubeIndices[i + 19] = 1;
            cubeIndices[i + 20] = 2;

            cubeIndices[i + 21] = 2;
            cubeIndices[i + 22] = 6;
            cubeIndices[i + 23] = 5;

            cubeIndices[i + 24] = 4;
            cubeIndices[i + 25] = 5;
            cubeIndices[i + 26] = 1;

            cubeIndices[i + 27] = 5;
            cubeIndices[i + 28] = 1;
            cubeIndices[i + 29] = 0;

            cubeIndices[i + 30] = 7;
            cubeIndices[i + 31] = 6;
            cubeIndices[i + 32] = 2;

            cubeIndices[i + 33] = 2;
            cubeIndices[i + 34] = 3;
            cubeIndices[i + 35] = 7;
        }

        Ref<IndexBuffer> cubeIndexBuffer = IndexBuffer::Create(cubeIndices, Renderer3DData::MaxIndices);
        s_Data.CubeVertexArray->SetIndexBuffer(cubeIndexBuffer);

        s_Data.CubeShader = Shader::Create("CubeShader",
                                           R"(D:\Files\S_Documents\Projects\Banana\BananaShake\assets\shaders\cube_vertex_shader.glsl)",
                                           R"(D:\Files\S_Documents\Projects\Banana\BananaShake\assets\shaders\cube_fragment_shader.glsl)",
                                           R"(D:\Files\S_Documents\Projects\Banana\BananaShake\assets\shaders\cube_geometry_shader.glsl)"
        );

        s_Data.CubeVertexPositions[0] = {-0.5f, -0.5f, -0.5f, 1.0f};
        s_Data.CubeVertexPositions[1] = {0.5f, -0.5f, -0.5f, 1.0f};
        s_Data.CubeVertexPositions[2] = {0.5f, 0.5f, -0.5f, 1.0f};
        s_Data.CubeVertexPositions[3] = {-0.5f, 0.5f, -0.5f, 1.0f};
        s_Data.CubeVertexPositions[4] = {-0.5f, -0.5f, 0.5f, 1.0f};
        s_Data.CubeVertexPositions[5] = {0.5f, -0.5f, 0.5f, 1.0f};
        s_Data.CubeVertexPositions[6] = {0.5f, 0.5f, 0.5f, 1.0f};
        s_Data.CubeVertexPositions[7] = {-0.5f, 0.5f, 0.5f, 1.0f};

        s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer3DData::CameraData), 0);
    };

    void Renderer3D::Shutdown() {
        BANANA_PROFILE_FUNCTION();
    }

    void Renderer3D::BeginScene(const EditorCamera &camera) {
        BANANA_PROFILE_FUNCTION();

        s_Data.CameraBuffer.ViewProjection = camera.GetViewProjection();
        s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(s_Data.CameraBuffer));

        StartBatch();
    }

    void Renderer3D::BeginScene(const Camera &camera, glm::mat4 &transform) {
        BANANA_PROFILE_FUNCTION();

        s_Data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);
        s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(s_Data.CameraBuffer));

        StartBatch();
    }

    void Renderer3D::EndScene() {
        BANANA_PROFILE_FUNCTION();

        Flush();
    }

    void Renderer3D::DrawCube(const glm::mat4 &transform, const glm::vec4 &color, int entityID) {
        BANANA_PROFILE_FUNCTION();

        constexpr size_t cubeVertexCount = 8;

        if (s_Data.CubeIndexCount >= Renderer3DData::MaxIndices) {
            FlushAndReset();
        }

        for (size_t i = 0; i < cubeVertexCount; i++) {
            s_Data.CubeVertexBufferPtr->Position = transform * s_Data.CubeVertexPositions[i];
            s_Data.CubeVertexBufferPtr->Color = color;
            s_Data.CubeVertexBufferPtr->EntityID = entityID;
            s_Data.CubeVertexBufferPtr++;
        }

        s_Data.CubeIndexCount += 36;
        s_Data.Stats.CubeCount++;
    }

    Renderer3D::Statistics Renderer3D::GetStats() {
        return s_Data.Stats;
    }

    void Renderer3D::ResetStats() {
        s_Data.Stats.CubeCount = 0;
        s_Data.Stats.DrawCalls = 0;
    }

    void Renderer3D::StartBatch() {
        s_Data.CubeIndexCount = 0;
        s_Data.CubeVertexBufferPtr = s_Data.CubeVertexBufferBase;
    }

    void Renderer3D::Flush() {
        BANANA_PROFILE_FUNCTION();

        if (s_Data.CubeIndexCount) {
            uint32_t dataSize = (uint32_t) ((uint8_t *) s_Data.CubeVertexBufferPtr - (uint8_t *) s_Data.
                                            CubeVertexBufferBase);
            s_Data.CubeVertexBuffer->SetData(s_Data.CubeVertexBufferBase, dataSize);

            s_Data.CubeShader->Bind();
            RenderCommand::DrawIndexed(s_Data.CubeVertexArray, s_Data.CubeIndexCount);
            s_Data.Stats.DrawCalls++;
        }
    }

    void Renderer3D::FlushAndReset() {
        EndScene();

        StartBatch();
    }
}
