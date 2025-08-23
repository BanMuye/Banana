//
// Created by 周春阳 on 2025/8/18.
//
#include "../../LibBanana/src/Banana/Core/Banana.h"
#include "spdlog/spdlog.h"

class SandboxApp : public Banana::Application {
public:
    SandboxApp() = default;

    ~SandboxApp() override = default;
};

int main(int argc, char *argv[]) {
    Banana::Log::Init();
    BANANA_INFO("Starting SandboxApp");
    const auto app = new SandboxApp();
    app->Run();
    delete app;
};
