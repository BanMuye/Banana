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
        glm::vec3 Normal;

        struct Material {
            glm::vec4 Ambient;
            glm::vec4 Diffuse;
            glm::vec4 Specular;
            float Shininess;
        };

        Material Material;

        // Editor-only
        int EntityID;
    };

    struct Renderer3DData {
        static constexpr uint32_t MaxCube = 10000;
        static constexpr uint32_t SingleCubeVertexCount = 36;
        static constexpr uint32_t SingleCubeIndicesCount = 36;
        static constexpr uint32_t MaxVertices = MaxCube * SingleCubeVertexCount;
        static constexpr uint32_t MaxIndices = MaxCube * SingleCubeIndicesCount;
        static constexpr glm::vec4 InitialCameraPosition = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        Ref<VertexArray> CubeVertexArray;
        Ref<VertexBuffer> CubeVertexBuffer;

        Ref<Shader> CubeShader;

        uint32_t CubeIndexCount = 0;
        CubeVertex *CubeVertexBufferBase = nullptr;
        CubeVertex *CubeVertexBufferPtr = nullptr;

        glm::vec3 CubeVertexPositions[SingleCubeVertexCount][2];

        Renderer3D::Statistics Stats{};

        struct CameraData {
            glm::mat4 ViewProjection;
            glm::vec3 Position;
        };

        CameraData CameraBuffer;
        Ref<UniformBuffer> CameraUniformBuffer;
        Ref<UniformBuffer> LightUniformBuffer;
    };

    static Renderer3DData s_Data;

    void Renderer3D::Init() {
        BANANA_PROFILE_FUNCTION();

        s_Data.CubeVertexArray = VertexArray::Create();
        s_Data.CubeVertexBuffer = VertexBuffer::Create(Renderer3DData::MaxVertices * sizeof(CubeVertex));
        s_Data.CubeVertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Normal"},
            {ShaderDataType::Float4, "a_Ambient"},
            {ShaderDataType::Float4, "a_Diffuse"},
            {ShaderDataType::Float4, "a_Specular"},
            {ShaderDataType::Float, "a_Shininess"},
            {ShaderDataType::Int, "a_EntityID"}
        });

        s_Data.CubeVertexArray->AddVertexBuffer(s_Data.CubeVertexBuffer);

        s_Data.CubeVertexBufferBase = new CubeVertex[Renderer3DData::MaxVertices];
        s_Data.CubeVertexBufferPtr = s_Data.CubeVertexBufferBase;

        uint32_t *cubeIndices = new uint32_t[Renderer3DData::MaxIndices];
        for (uint32_t i = 0; i < Renderer3DData::MaxIndices; i++) {
            cubeIndices[i] = i;
        }

        Ref<IndexBuffer> cubeIndexBuffer = IndexBuffer::Create(cubeIndices, Renderer3DData::MaxIndices);
        s_Data.CubeVertexArray->SetIndexBuffer(cubeIndexBuffer);

        s_Data.CubeShader = Shader::Create("CubeShader",
                                           R"(D:\Files\S_Documents\Projects\Banana\BananaShake\assets\shaders\cube_vertex_shader.glsl)",
                                           R"(D:\Files\S_Documents\Projects\Banana\BananaShake\assets\shaders\cube_fragment_shader.glsl)",
                                           R"(D:\Files\S_Documents\Projects\Banana\BananaShake\assets\shaders\cube_geometry_shader.glsl)"
        );

        float rawData[] = {
            // 每组：位置(x,y,z)，法线(nx,ny,nz)
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
        };

        for (int i = 0; i < 36; ++i) {
            s_Data.CubeVertexPositions[i][0] = glm::vec3(rawData[i * 6 + 0], rawData[i * 6 + 1], rawData[i * 6 + 2]);
            // 位置
            s_Data.CubeVertexPositions[i][1] = glm::vec3(rawData[i * 6 + 3], rawData[i * 6 + 4], rawData[i * 6 + 5]);
            // 法线
        }

        s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer3DData::CameraData), 0);
        s_Data.LightUniformBuffer = UniformBuffer::Create(sizeof(LightData), 1);
    };

    void Renderer3D::Shutdown() {
        BANANA_PROFILE_FUNCTION();
    }

    void Renderer3D::BeginScene(const EditorCamera &camera, const LightController &lightController) {
        BANANA_PROFILE_FUNCTION();

        s_Data.CameraBuffer.ViewProjection = camera.GetViewProjection();
        s_Data.CameraBuffer.Position = camera.GetPosition();
        s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(s_Data.CameraBuffer));
        s_Data.CameraUniformBuffer->SetData(&s_Data.LightUniformBuffer, sizeof(lightController.GetLightData()));

        ResetStats();
        StartBatch();
    }

    void Renderer3D::BeginScene(const Camera &camera, glm::mat4 &transform, const LightController &lightController) {
        BANANA_PROFILE_FUNCTION();

        s_Data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);
        s_Data.CameraBuffer.Position = transform * Renderer3DData::InitialCameraPosition;
        s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(s_Data.CameraBuffer));
        s_Data.CameraUniformBuffer->SetData(&s_Data.LightUniformBuffer, sizeof(lightController.GetLightData()));

        ResetStats();
        StartBatch();
    }

    void Renderer3D::EndScene() {
        BANANA_PROFILE_FUNCTION();

        Flush();
    }

    void Renderer3D::DrawCube(const glm::mat4 &transform, const glm::vec4 &ambient,
                              const glm::vec4 &diffuse, const glm::vec4 &specular, const float &shininess,
                              int entityID) {
        BANANA_PROFILE_FUNCTION();

        constexpr size_t cubeVertexCount = Renderer3DData::SingleCubeVertexCount;

        if (s_Data.CubeIndexCount >= Renderer3DData::MaxIndices) {
            FlushAndReset();
        }

        for (size_t i = 0; i < cubeVertexCount; i++) {
            s_Data.CubeVertexBufferPtr->Position = transform * glm::vec4(s_Data.CubeVertexPositions[i][0], 1.0f);
            s_Data.CubeVertexBufferPtr->Normal = s_Data.CubeVertexPositions[i][1];
            s_Data.CubeVertexBufferPtr->Material.Ambient = ambient;
            s_Data.CubeVertexBufferPtr->Material.Diffuse = diffuse;
            s_Data.CubeVertexBufferPtr->Material.Specular = specular;
            s_Data.CubeVertexBufferPtr->Material.Shininess = shininess;
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
