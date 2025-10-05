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

#include "Banana/Core/Application.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f, true) {
}

void Sandbox2D::OnAttach() {
    BANANA_PROFILE_FUNCTION();

    m_Texture = Banana::Texture2D::Create(
        "D:\\Files\\S_Documents\\Projects\\Banana\\Sandbox\\assets\\IMG_5291.JPG");

    Banana::FramebufferSpecification fbSpec;
    fbSpec.Width = 400;
    fbSpec.Height = 300;
    m_Framebuffer = Banana::Framebuffer::Create(fbSpec);
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

    m_Framebuffer->Bind();

    Banana::RenderCommand::SetClearColor({0.1f, 0.2f, 0.3f, 1.0f});
    Banana::RenderCommand::Clear();

    Banana::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Banana::Renderer2D::DrawQuad(glm::vec3(9.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), m_SquareColor);
    Banana::Renderer2D::DrawQuad(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), m_SquareColor);
    Banana::Renderer2D::DrawRotatedQuad(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 45,
                                        m_SquareColor);
    Banana::Renderer2D::DrawQuad(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(16.0f, 9.0f), m_Texture, 10);
    Banana::Renderer2D::EndScene();

    m_Framebuffer->Unbind();
}

void Sandbox2D::OnImGuiRender() {
    static bool dockingEnabled = true;
    if (dockingEnabled) {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        // bool opt_fullscreen = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
            window_flags |= ImGuiWindowFlags_NoBackground;
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen) {
            ImGui::PopStyleVar(2);
        }

        // DockSpace
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    Banana::Application::Get().Close();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::Begin("Settings");

        auto stats = Banana::Renderer2D::GetStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

        ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImVec2 uv0 = ImVec2(0.0f, 1.0f); // 左下角 -> 正常左上角
        ImVec2 uv1 = ImVec2(1.0f, 0.0f); // 右上角 -> 正常右下角
        ImGui::Image(textureID, ImVec2{400, 300}, uv0, uv1);
        ImGui::End();

        ImGui::End();
    } else {
        auto statistics = Banana::Renderer2D::GetStats();
        ImGui::Text("Renderer0D Stats:");
        ImGui::Text("Draw Calls: %d", statistics.DrawCalls);
        ImGui::Text("Quads: %d", statistics.QuadCount);
        ImGui::Text("Vertices: %d", statistics.GetTotalVertexCount());
        ImGui::Text("Indices: %d", statistics.GetTotalIndexCount());
        ImGui::End();
    }
}

void Sandbox2D::OnEvent(Banana::Event &event) {
    m_CameraController.OnEvent(event);
}
