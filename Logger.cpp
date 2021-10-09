#include "Logger.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Logger::coreLogger;
std::shared_ptr<spdlog::logger> Logger::soundLogger;

void Logger::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    coreLogger = spdlog::stdout_color_mt("CORE");
    coreLogger->set_level(spdlog::level::trace);
    soundLogger = spdlog::stdout_color_mt("SOUNDENGINE");
    soundLogger->set_level(spdlog::level::trace);
}
