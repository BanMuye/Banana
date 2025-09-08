//
// Created by 周春阳 on 2025/8/18.
//
#include "../../LibBanana/src/Banana/Core/Banana.h"
#include "Banana/Core/Input.h"
#include "Banana/Core/KeyCodes.h"
#include "Banana/Renderer/Renderer.h"
#include "spdlog/spdlog.h"

class ExampleLayer : public Banana::Layer {
public:
    ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
        m_RectangleVA.reset(Banana::VertexArray::Create());

        float vertices[3 * 8] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.1f, 0.8f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        std::shared_ptr<Banana::VertexBuffer> rectangleVB;
        rectangleVB.reset(Banana::VertexBuffer::Create(vertices, sizeof(vertices)));

        Banana::BufferLayout layout = {
            {Banana::ShaderDataType::Float4, "a_Position"},
            {Banana::ShaderDataType::Float4, "a_Color"}
        };

        rectangleVB->SetLayout(layout);
        m_RectangleVA->AddVertexBuffer(rectangleVB);

        std::shared_ptr<Banana::IndexBuffer> rectangleIB;
        unsigned int indices[3] = {0, 1, 2};
        rectangleIB.reset(Banana::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));

        m_RectangleVA->SetIndexBuffer(rectangleIB);

        std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec4 a_Position;
            layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec4 v_Position;
            out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * a_Position;
                v_Color = a_Color;
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
            in vec4 v_Color;

			void main()
			{
                color = v_Color;
			}
		)";

        m_Shader.reset(new Banana::Shader(vertexSrc, fragmentSrc));


        m_SquareVA.reset(Banana::VertexArray::Create());

        std::shared_ptr<Banana::VertexBuffer> squareVB;
        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f, 0.75f, 0.0f,
            -0.75f, 0.75f, 0.0f
        };

        squareVB.reset(Banana::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        Banana::BufferLayout squareLayout = {{Banana::ShaderDataType::Float3, "a_Position"}};
        squareVB->SetLayout(squareLayout);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<Banana::IndexBuffer> squareIB;
        squareIB.reset(Banana::IndexBuffer::Create(squareIndices, 6));
        m_SquareVA->AddVertexBuffer(squareVB);
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

        std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.8, 0.3, 0.8, 1.0);
			}
		)";

        blue_Shader.reset(new Banana::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    void OnUpdate(const Banana::Timestep timestep) override {
        if (Banana::Input::IsKeyPressed(BANANA_KEY_LEFT))
            m_CameraPosition.x += m_CameraMoveSpeed * timestep;
        else if (Banana::Input::IsKeyPressed(BANANA_KEY_RIGHT))
            m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
        if (Banana::Input::IsKeyPressed(BANANA_KEY_UP))
            m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
        if (Banana::Input::IsKeyPressed(BANANA_KEY_DOWN))
            m_CameraPosition.y += m_CameraMoveSpeed * timestep;

        if (Banana::Input::IsKeyPressed(BANANA_KEY_A))
            m_CameraRotation -= m_CameraRotationSpeed * timestep;
        if (Banana::Input::IsKeyPressed(BANANA_KEY_D))
            m_CameraRotation += m_CameraRotationSpeed * timestep;

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Banana::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Banana::RenderCommand::Clear();

        Banana::Renderer::BeginScene(m_Camera);
        Banana::Renderer::Submit(blue_Shader, m_SquareVA);
        Banana::Renderer::Submit(m_Shader, m_RectangleVA);
        Banana::Renderer::EndScene();
    }

    void OnEvent(Banana::Event &event) override {
    }

private :
    std::shared_ptr<Banana::Shader> m_Shader;
    std::shared_ptr<Banana::VertexArray> m_RectangleVA;

    std::shared_ptr<Banana::Shader> blue_Shader;
    std::shared_ptr<Banana::VertexArray> m_SquareVA;

    Banana::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f;
};

class SandboxApp : public Banana::Application {
public:
    SandboxApp() = default;

    ~SandboxApp() override = default;
};

int main(int argc, char *argv[]) {
    Banana::Log::Init();
    BANANA_INFO("Starting SandboxApp");
    const auto app = new SandboxApp();

    app->PushLayer(new ExampleLayer());

    app->Run();
    delete app;
};
