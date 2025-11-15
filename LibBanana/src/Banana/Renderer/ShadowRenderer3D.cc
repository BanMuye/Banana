//
// Created by cyzho on 2025/11/5.
//

#include "Banana/Core/bapch.h"
#include "ShadowRenderer3D.h"

#include <entt/entity/entity.hpp>

#include "RenderCommand.h"
#include "Shader.h"
#include "UniformBuffer.h"
#include "VertexArray.h"
#include "Banana/Core/Core.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace Banana {
    struct CubeVertex {
        glm::vec3 Position;
    };

    struct LightSpace {
        glm::mat4 ViewProjection;
    };

    struct ShadowRenderer3DData {
        static constexpr uint32_t MaxCube = 10000;
        static constexpr uint32_t SingleCubeVertexCount = 36;
        static constexpr uint32_t SingleCubeIndicesCount = 36;
        static constexpr uint32_t MaxVertices = MaxCube * SingleCubeVertexCount;
        static constexpr uint32_t MaxIndices = MaxCube * SingleCubeIndicesCount;
        static constexpr glm::vec4 InitialCameraPosition = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        Ref<VertexArray> CubeVertexArray;
        Ref<VertexBuffer> CubeVertexBuffer;

        Ref<Shader> ShadowShader;

        uint32_t CubeIndexCount = 0;
        CubeVertex *CubeVertexBufferBase = nullptr;
        CubeVertex *CubeVertexBufferPtr = nullptr;

        glm::vec3 CubeVertexPositions[SingleCubeVertexCount];

        LightSpace LightSpaceBufferData;
        Ref<UniformBuffer> LightSpaceUniformBuffer;
    };

    static ShadowRenderer3DData s_Data;

    void ShadowRenderer3D::Init() {
        s_Data.CubeVertexArray = VertexArray::Create();
        s_Data.CubeVertexBuffer = VertexBuffer::Create(ShadowRenderer3DData::MaxVertices * sizeof(CubeVertex));
        s_Data.CubeVertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"}
        });
        s_Data.CubeVertexArray->AddVertexBuffer(s_Data.CubeVertexBuffer);

        s_Data.CubeVertexBufferBase = new CubeVertex[ShadowRenderer3DData::MaxVertices];
        s_Data.CubeVertexBufferPtr = s_Data.CubeVertexBufferBase;


        uint32_t *cubeIndices = new uint32_t[ShadowRenderer3DData::MaxIndices];
        for (uint32_t i = 0; i < ShadowRenderer3DData::MaxIndices; i++) {
            cubeIndices[i] = i;
        }

        Ref<IndexBuffer> cubeIndexBuffer = IndexBuffer::Create(cubeIndices, ShadowRenderer3DData::MaxIndices);
        s_Data.CubeVertexArray->SetIndexBuffer(cubeIndexBuffer);


        s_Data.ShadowShader = Shader::Create("ShadowShader",
                                             R"(D:\Files\S_Documents\Projects\Banana\BananaShake\assets\shaders\shadow_mapping_vertex_shader.glsl)",
                                             R"(D:\Files\S_Documents\Projects\Banana\BananaShake\assets\shaders\shadow_mapping_fragment_shader.glsl)",
                                             R"(D:\Files\S_Documents\Projects\Banana\BananaShake\assets\shaders\shadow_mapping_geometry_shader.glsl)"
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
            s_Data.CubeVertexPositions[i] = glm::vec3(rawData[i * 6 + 0], rawData[i * 6 + 1], rawData[i * 6 + 2]);
        }

        s_Data.LightSpaceUniformBuffer = UniformBuffer::Create(sizeof(LightSpace), 2);
    }

    void ShadowRenderer3D::Shutdown() {
    }

    void ShadowRenderer3D::BeginScene(const LightController &lightController) {

        CalcLightSpaceViewProjection(lightController);
        s_Data.LightSpaceUniformBuffer->SetData(&s_Data.LightSpaceBufferData, sizeof(LightSpace));

        StartBatch();
    }

    void ShadowRenderer3D::EndScene() {
        Flush();
    }

    void ShadowRenderer3D::DrawCube(const glm::mat4 &transform) {
        constexpr size_t cubeVertexCount = ShadowRenderer3DData::SingleCubeVertexCount;

        if (s_Data.CubeIndexCount >= ShadowRenderer3DData::MaxIndices) {
            FlushAndReset();
        }

        for (size_t i = 0; i < cubeVertexCount; i++) {
            s_Data.CubeVertexBufferPtr->Position = xyz( transform * glm::vec4(s_Data.CubeVertexPositions[i], 1.0f));
            s_Data.CubeVertexBufferPtr++;
        }

        s_Data.CubeIndexCount += 36;
    }

    void ShadowRenderer3D::StartBatch() {
        s_Data.CubeVertexBufferPtr = s_Data.CubeVertexBufferBase;
        s_Data.CubeIndexCount = 0;
    }

    void ShadowRenderer3D::Flush() {
        if (s_Data.CubeIndexCount) {
            uint32_t dataSize = (uint32_t) ((uint8_t *) s_Data.CubeVertexBufferPtr - (uint8_t *) s_Data.
                                            CubeVertexBufferBase);
            s_Data.CubeVertexBuffer->SetData(s_Data.CubeVertexBufferBase, dataSize);

            s_Data.ShadowShader->Bind();
            RenderCommand::DrawIndexed(s_Data.CubeVertexArray, s_Data.CubeIndexCount);
        }
    }

    void ShadowRenderer3D::FlushAndReset() {
        EndScene();
        StartBatch();
    }

    void ShadowRenderer3D::CalcLightSpaceViewProjection(const LightController &lightController) {
        auto lightData = lightController.GetLightData();

        // currently we only support shadow from directional light
        if (lightData.directionalLightCount < 1) return;

        auto directionalLight = lightData.DirectionalLights[0];

        float nearPlane = -1.0f, farPlane = 1.0f;
        glm::mat4 lightProjection = glm::ortho(-1.280f, 1.280f, -0.720f, 0.720f, nearPlane, farPlane);

        glm::mat4 lightView = glm::lookAt(xyz(LightController::s_InitialLightPosition), xyz(directionalLight.Direction),
                                          glm::vec3(0.0f, 1.0f, 0.0f));

        s_Data.LightSpaceBufferData.ViewProjection = lightProjection * lightView;
    }
}
