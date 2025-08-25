//
// Created by 周春阳 on 2025/8/18.
//
#include "../../LibBanana/src/Banana/Core/Banana.h"
#include "spdlog/spdlog.h"

class ExampleLayer : public Banana::Layer {
public:
    ExampleLayer() : Layer("Example") {
    }

    void OnUpdate() override {
        BANANA_INFO("ExampleLayer::OnUpdate");
    }

    void OnEvent(Banana::Event &event) override {
        BANANA_INFO("ExampleLayer::OnEvent, {0}", event.ToString());
    }
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
