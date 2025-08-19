//
// Created by 周春阳 on 2025/8/18.
//
#include <iostream>
#include "Banana/Banana.h"
#include "spdlog/spdlog.h"

class SandboxApp : public Banana::Application {
public:
    SandboxApp() = default;

    ~SandboxApp() override = default;
};

int main(int argc, char *argv[]) {
    Banana::Log::Init();
    Banana::Log::GetCoreLogger()->info("Sandbox application Core Logger Test");
    auto app = new SandboxApp();
    app->Run();
    delete app;
};
