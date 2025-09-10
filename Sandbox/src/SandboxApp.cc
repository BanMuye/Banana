//
// Created by 周春阳 on 2025/8/18.
//
#include "imgui.h"
#include "Banana/Core/Banana.h"
#include "Banana/Core/Input.h"
#include "Banana/Core/KeyCodes.h"
#include "Banana/Renderer/Renderer.h"
#include "glm/gtx/transform.hpp"
#include "spdlog/spdlog.h"
#include "Banana/Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.inl"

class ExampleLayer : public Banana::Layer {
public:
    ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
        m_RectangleVA.reset(Banana::VertexArray::Create());

        float vertices[3 * 8] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.1f, 0.8f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        Banana::Ref<Banana::VertexBuffer> rectangleVB;
        rectangleVB.reset(Banana::VertexBuffer::Create(vertices, sizeof(vertices)));

        Banana::BufferLayout layout = {
            {Banana::ShaderDataType::Float4, "a_Position"},
            {Banana::ShaderDataType::Float4, "a_Color"}
        };

        rectangleVB->SetLayout(layout);
        m_RectangleVA->AddVertexBuffer(rectangleVB);

        Banana::Ref<Banana::IndexBuffer> rectangleIB;
        unsigned int indices[3] = {0, 1, 2};
        rectangleIB.reset(Banana::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));

        m_RectangleVA->SetIndexBuffer(rectangleIB);

        std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec4 a_Position;
            layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Position;
            out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * a_Position;
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


        m_RectangleShader.reset(Banana::Shader::Create(vertexSrc, fragmentSrc));

        m_SquareVA.reset(Banana::VertexArray::Create());

        Banana::Ref<Banana::VertexBuffer> squareVB;
        float squareVertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };

        squareVB.reset(Banana::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        Banana::BufferLayout squareLayout = {
            {Banana::ShaderDataType::Float3, "a_Position"}, {Banana::ShaderDataType::Float2, "a_TexCoord"}
        };
        squareVB->SetLayout(squareLayout);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        Banana::Ref<Banana::IndexBuffer> squareIB;
        squareIB.reset(Banana::IndexBuffer::Create(squareIndices, 6));
        m_SquareVA->AddVertexBuffer(squareVB);
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

        std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

        m_SquareShader.reset(Banana::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));

        m_TextureVA.reset(Banana::VertexArray::Create());
        float textureVertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };
        Banana::Ref<Banana::VertexBuffer> textureVB;
        textureVB.reset(
            Banana::VertexBuffer::Create(textureVertices, sizeof(textureVertices)));
        textureVB->SetLayout({
            {Banana::ShaderDataType::Float3, "a_Position"}, {Banana::ShaderDataType::Float2, "a_TexCoord"}
        });

        Banana::Ref<Banana::IndexBuffer> textureIB;
        unsigned int textureIndices[6] = {0, 1, 2, 2, 3, 0};
        textureIB.reset(
            Banana::IndexBuffer::Create(textureIndices, sizeof(textureIndices) / sizeof(textureIndices[0])));
        m_TextureVA->AddVertexBuffer(textureVB);
        m_TextureVA->SetIndexBuffer(textureIB);

        std::string textureVertexSrc = R"(
           #version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location =1 ) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec2 v_TexCoord;

			void main()
			{
				v_Position = a_Position;
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
        )";

        std::string textureFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main() {
				color = texture(u_Texture, v_TexCoord);
			}
		)";

        m_TextureShader.reset(Banana::Shader::Create(textureVertexSrc, textureFragmentSrc));

    	std::string path = "/Users/zhouchunyang/Documents/Projects/Banana/Sandbox/assets/ChernoLogo.png";
        m_Texture.reset(
            Banana::Texture2D::Create(path));

        std::dynamic_pointer_cast<Banana::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<Banana::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(const Banana::Timestep timestep) override {
        if (Banana::Input::IsKeyPressed(BANANA_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
        else if (Banana::Input::IsKeyPressed(BANANA_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed * timestep;
        if (Banana::Input::IsKeyPressed(BANANA_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed * timestep;
        if (Banana::Input::IsKeyPressed(BANANA_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed * timestep;

        if (Banana::Input::IsKeyPressed(BANANA_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed * timestep;
        if (Banana::Input::IsKeyPressed(BANANA_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed * timestep;

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Banana::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Banana::RenderCommand::Clear();

        Banana::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1));
        glm::vec3 color = glm::vec3(0.0, 0.0, 0.0);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                glm::vec3 pos = glm::vec3(i * 0.21, j * 0.21, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                color.r = m_SquareColor.r + i * 0.02;
                color.g = m_SquareColor.g + i * 0.05;
                color.b = m_SquareColor.b + i * 0.02;
                m_SquareShader->Bind();
                std::dynamic_pointer_cast<Banana::OpenGLShader>(m_SquareShader)->UploadUniformFloat3("u_Color", color);
                Banana::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
            }
        }


        Banana::Renderer::Submit(m_RectangleShader, m_RectangleVA);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1, -1, 0));
        Banana::Renderer::Submit(m_TextureShader, m_TextureVA, transform);
        Banana::Renderer::EndScene();
    }


    void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Banana::Event &event) override {
    }

private :
    Banana::Ref<Banana::Shader> m_RectangleShader;
    Banana::Ref<Banana::VertexArray> m_RectangleVA;

    Banana::Ref<Banana::Shader> m_SquareShader;
    Banana::Ref<Banana::VertexArray> m_SquareVA;

    Banana::Ref<Banana::Shader> m_TextureShader;
    Banana::Ref<Banana::VertexArray> m_TextureVA;
    Banana::Ref<Banana::Texture> m_Texture;

    Banana::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f;

    glm::vec3 m_SquareColor = glm::vec3(0.0f);
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
