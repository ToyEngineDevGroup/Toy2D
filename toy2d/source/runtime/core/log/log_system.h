#pragma once

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace Toy2D {
    class LogSystem {
    public:
        static void init();

        static std::shared_ptr<spdlog::logger>& getLogger() { return s_logger; }

    private:
        static std::shared_ptr<spdlog::logger> s_logger;
    };

} // namespace Toy2D

// Core log macros
#define LOG_TRACE(...) ::Toy2D::LogSystem::getLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::Toy2D::LogSystem::getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Toy2D::LogSystem::getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Toy2D::LogSystem::getLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...) ::Toy2D::LogSystem::getLogger()->fatal(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Toy2D::LogSystem::getLogger()->critical(__VA_ARGS__)
