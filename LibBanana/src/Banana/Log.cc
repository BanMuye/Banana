//
// Created by 周春阳 on 2025/8/19.
//

#include "Banana/Log.h"


namespace Banana {
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("Banana Core");
        s_CoreLogger->set_level(spdlog::level::trace);
        s_ClientLogger = spdlog::stdout_color_mt("Banana Client");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}
