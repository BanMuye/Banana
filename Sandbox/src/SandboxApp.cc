//
// Created by 周春阳 on 2025/8/18.
//
#include "EditorLayer.h"
#include "imgui.h"
#include "Sandbox2D.h"
#include "Banana/Core/Banana.h"
#include "Banana/Core/Input.h"
#include "Banana/Core/KeyCodes.h"
#include "Banana/Core/OrthographicCameraController.h"
#include "Banana/Debug/Instrumentor.h"
#include "Banana/Renderer/Renderer.h"
#include "glm/gtx/transform.hpp"
#include "spdlog/spdlog.h"
#include "Banana/Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.inl"

class SandboxApp : public Banana::Application {
public:
    SandboxApp() {
        PushLayer(new Banana::EditorLayer());
    } ;

    ~SandboxApp() override = default;
};

int main(int argc, char *argv[]) {
    Banana::Log::Init();

    BANANA_PROFILE_BEGIN_SESSION("Startup", "BananaProfile-Startup.json");
    const auto app = new SandboxApp();
    BANANA_PROFILE_END_SESSION()

    BANANA_PROFILE_BEGIN_SESSION("Runtime", "BananaProfile-Runtime.json");
    app->Run();
    BANANA_PROFILE_END_SESSION()

    BANANA_PROFILE_BEGIN_SESSION("Cleanup", "BananaProfile-Cleanup.json");
    delete app;
    BANANA_PROFILE_END_SESSION()
};
