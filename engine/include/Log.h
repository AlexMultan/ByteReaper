//
// Created by alex on 5/4/26.
//

#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

#define REAPER_CORE_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define REAPER_CORE_INFO(...)  ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define REAPER_CORE_WARN(...)  ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define REAPER_CORE_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define REAPER_CORE_CRITICAL(...) ::Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define REAPER_TRACE(...) ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define REAPER_INFO(...)  ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define REAPER_WARN(...)  ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define REAPER_ERROR(...) ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define REAPER_CRITICAL(...) ::Engine::Log::GetClientLogger()->critical(__VA_ARGS__)


namespace Engine {

    class ENGINE_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
        {
            return s_CoreLogger;
        }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
        {
            return s_ClientLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}
