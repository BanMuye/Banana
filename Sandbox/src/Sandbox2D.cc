//
// Created by 周春阳 on 2025/9/11.
//

#include "Sandbox2D.h"

#include "imgui.h"
#include "Banana/Platform/OpenGL/OpenGLShader.h"
#include "Banana/Renderer/RenderCommand.h"
#include "Banana/Renderer/Renderer.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f) {
}

void Sandbox2D::OnAttach() {
    m_SquareVA = Banana::VertexArray::Create();
    float squareVertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    Banana::Ref<Banana::VertexBuffer> squareVB;
    squareVB.reset(Banana::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({
        {Banana::ShaderDataType::Float3, "a_Position"}
    });
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    Banana::Ref<Banana::IndexBuffer> squareIE;
    squareIE.reset(Banana::IndexBuffer::Create(squareIndices, 6));
    m_SquareVA->SetIndexBuffer(squareIE);

    m_FlatColorShader = Banana::Shader::Create("FlatColorShader",
                                               "/Users/zhouchunyang/Documents/Projects/Banana/Sandbox/assets/shaders/flat_color_vertex_shader.glsl",
                                               "/Users/zhouchunyang/Documents/Projects/Banana/Sandbox/assets/shaders/flat_color_fragment_shader.glsl",
                                               "/Users/zhouchunyang/Documents/Projects/Banana/Sandbox/assets/shaders/flat_color_geometry_shader.glsl");
}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(Banana::Timestep ts) {
    // update
    m_CameraController.OnUpdate(ts);

    Banana::RenderCommand::SetClearColor({0.1f, 0.2f, 0.3f, 1.0f});
    Banana::RenderCommand::Clear();

    Banana::Renderer::BeginScene(m_CameraController.GetCamera());
    std::dynamic_pointer_cast<Banana::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Banana::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
    Banana::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0F), glm::vec3(1.5f)));
    Banana::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Banana::Event &event) {
    m_CameraController.OnEvent(event);

}
