//
// Created by 周春阳 on 2025/8/18.
//
#include <iostream>
#include "Banana/Renderer/Renderer.h"
#include "Application.h"


#include "Log.h"
#include "Banana/ImGui/ImGuiLayer.h"
#include "Banana/Platform/MacOS/MacOSWindow.h"
#include "Banana/Renderer/Buffer.h"

namespace Banana {
#define BIND_EVENT_FN(function) std::bind(&Application::function, this, std::placeholders::_1)

    Application *Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(MacOSWindow::Create());
        m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        m_RectangleVA.reset(VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        std::shared_ptr<VertexBuffer> rectangleVB;
        rectangleVB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"}
        };

        rectangleVB->SetLayout(layout);
        m_RectangleVA->AddVertexBuffer(rectangleVB);

        std::shared_ptr<IndexBuffer> rectangleIB;
        unsigned int indices[3] = {0, 1, 2};
        rectangleIB.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));

        m_RectangleVA->SetIndexBuffer(rectangleIB);

        std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
            out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
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

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));


        m_SquareVA.reset(VertexArray::Create());

        std::shared_ptr<VertexBuffer> squareVB;
        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f, 0.75f, 0.0f,
            -0.75f, 0.75f, 0.0f
        };

        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        BufferLayout squareLayout = {{ShaderDataType::Float3, "a_Position"}};
        squareVB->SetLayout(squareLayout);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, 6));
        m_SquareVA->AddVertexBuffer(squareVB);
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
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

        blue_Shader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    Application::~Application() = default;

    void Application::Run() {
        while (m_IsRunning) {
        	RenderCommand::SetClearColor({0.1, 0.2, 0.1, 1});
        	RenderCommand::Clear();

        	Renderer::BeginScene();

            blue_Shader->Bind();
        	Renderer::Submit(m_SquareVA);

            m_Shader->Bind();
        	Renderer::Submit(m_RectangleVA);

        	Renderer::EndScene();

            for (Layer *layer: m_LayerStack) {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer *layer: m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        BANANA_CORE_TRACE("{0}", event.ToString());

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(event);
            if (event.Handled)break;
        }
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent &event) {
        m_IsRunning = false;
        return true;
    }
}
