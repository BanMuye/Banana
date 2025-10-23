//
// Created by 周春阳 on 2025/8/19.
//

#ifndef BANANA_LOG_H
#define BANANA_LOG_H

#include <memory>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include "Core.h"
#include "spdlog/logger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks-inl.h"

namespace Banana {
    class API_EXPORT Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }

        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; };

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define BANANA_CORE_ERROR(...) ::Banana::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BANANA_CORE_WARN(...) ::Banana::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BANANA_CORE_INFO(...) ::Banana::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BANANA_CORE_DEBUG(...) ::Banana::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define BANANA_CORE_TRACE(...) ::Banana::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BANANA_ERROR(...) ::Banana::Log::GetClientLogger()->error(__VA_ARGS__)
#define BANANA_WARN(...) ::Banana::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BANANA_INFO(...) ::Banana::Log::GetClientLogger()->info(__VA_ARGS__)
#define BANANA_DEBUG(...) ::Banana::Log::GetClientLogger()->debug(__VA_ARGS__)
#define BANANA_TRACE(...) ::Banana::Log::GetClientLogger()->trace(__VA_ARGS__)


#endif //BANANA_LOG_H
