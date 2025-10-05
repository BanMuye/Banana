//
// Created by 周春阳 on 2025/9/11.
//

#include "Sandbox2D.h"
#include "imgui.h"
#include "Banana/Platform/OpenGL/OpenGLShader.h"
#include "Banana/Renderer/RenderCommand.h"
#include "Banana/Renderer/Renderer.h"
#include "Banana/Renderer/Renderer2D.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

#include <chrono>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f, true) {
}

void Sandbox2D::OnAttach() {
    BANANA_PROFILE_FUNCTION();
    m_Texture = Banana::Texture2D::Create(
        "D:\\Files\\S_Documents\\Projects\\Banana\\Sandbox\\assets\\IMG_5291.JPG");
}

void Sandbox2D::OnDetach() {
    BANANA_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Banana::Timestep ts) {
    BANANA_PROFILE_FUNCTION();
    // update
    {
        BANANA_PROFILE_SCOPE("CameraController::OnUpdate");
        m_CameraController.OnUpdate(ts);
    }

    Banana::Renderer2D::ResetStats();
    Banana::RenderCommand::SetClearColor({0.1f, 0.2f, 0.3f, 1.0f});
    Banana::RenderCommand::Clear();

    Banana::Renderer2D::BeginScene(m_CameraController.GetCamera());
    // Banana::Renderer2D::DrawQuad(glm::vec3(9.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), m_SquareColor);
    // Banana::Renderer2D::DrawQuad(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), m_SquareColor);
    // Banana::Renderer2D::DrawRotatedQuad(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 45,
    // m_SquareColor);
    // Banana::Renderer2D::DrawQuad(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(16.0f, 9.0f), m_Texture, 10);
    Banana::Renderer2D::EndScene();

    // test batch rendering
    Banana::Renderer2D::BeginScene(m_CameraController.GetCamera());
    for (float y = -5.0f; y < 5.0f; y += 0.05f) {
        for (float x = -5.0f; x < 5.0f; x += 0.05f) {
            glm::vec4 color = {(x+5.0f)/10.0f, 0.4f, (y+5.0f)/10.0f, 1.0f};
            Banana::Renderer2D::DrawQuad({x, y}, {0.045f, 0.045f}, color);
        }
    }
    Banana::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    auto statistics = Banana::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", statistics.DrawCalls);
    ImGui::Text("Quads: %d", statistics.QuadCount);
    ImGui::Text("Vertices: %d", statistics.GetTotalVertexCount());
    ImGui::Text("Indices: %d", statistics.GetTotalIndexCount());
    ImGui::End();
}

void Sandbox2D::OnEvent(Banana::Event &event) {
    m_CameraController.OnEvent(event);
}
