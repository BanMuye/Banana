#include "EditorLayer.h"
#include "Banana/Core/Application.h"
//
// Created by cyzho on 2025/10/7.
//
namespace Banana {
    class BananaShake : public Application {
    public:
        BananaShake(ApplicationCommandLineArgs args) : Application("Banana Shake", args) {
            PushLayer(new EditorLayer());
        }

        ~BananaShake() override = default;
    };
}

int main(int argc, char *argv[]) {
    Banana::Log::Init();

    BANANA_PROFILE_BEGIN_SESSION("Startup", "BananaProfile-Startup.json");
    const auto app = new Banana::BananaShake({argc, argv});
    BANANA_PROFILE_END_SESSION()

    BANANA_PROFILE_BEGIN_SESSION("Runtime", "BananaProfile-Runtime.json");
    app->Run();
    BANANA_PROFILE_END_SESSION()

    BANANA_PROFILE_BEGIN_SESSION("Cleanup", "BananaProfile-Cleanup.json");
    delete app;
    BANANA_PROFILE_END_SESSION()
};
