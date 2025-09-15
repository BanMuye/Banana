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

template<typename Fn>
class Timer {
public:
    Timer(const char *name, Fn &&func) : m_Name(name), m_Func(func), m_Stopped(false) {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        if (!m_Stopped) {
            Stop();
        }
    }

    void Stop() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().
                count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().
                count();

        m_Stopped = true;

        float duration = (end - start) * 0.001f;

        m_Func({m_Name, duration});
    }

private:
    const char *m_Name;
    Fn m_Func;
    std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
    bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(#name, [&](ProfileResult result){m_ProfileResults.push_back(result);})

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f, true) {
}

void Sandbox2D::OnAttach() {
    m_Texture = Banana::Texture2D::Create(
        "/Users/zhouchunyang/Documents/Projects/Banana/Sandbox/assets/IMG_5291.JPG");
}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(Banana::Timestep ts) {
    PROFILE_SCOPE("Sandbox2D::OnUpate");
    // update
    m_CameraController.OnUpdate(ts);

    Banana::RenderCommand::SetClearColor({0.1f, 0.2f, 0.3f, 1.0f});
    Banana::RenderCommand::Clear();

    Banana::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Banana::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), m_SquareColor);
    Banana::Renderer2D::DrawQuad(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(16.0f, 9.0f), m_Texture);
    Banana::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    for (auto& result: m_ProfileResults) {
        char label[50];
        strcpy(label, "%.3fms ");
        strcat(label, result.Name);
        ImGui::Text(label, result.Time);
    }
    m_ProfileResults.clear();

    ImGui::End();
}

void Sandbox2D::OnEvent(Banana::Event &event) {
    m_CameraController.OnEvent(event);
}
