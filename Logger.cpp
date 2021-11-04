#include "Logger.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>

std::shared_ptr<spdlog::logger> Logger::coreLogger;
std::shared_ptr<spdlog::logger> Logger::soundLogger;
std::shared_ptr<spdlog::logger> Logger::fmodLogger;

void Logger::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    coreLogger = spdlog::stdout_color_mt("CORE");
    coreLogger->set_level(spdlog::level::trace);
    soundLogger = spdlog::stdout_color_mt("SOUNDENGINE");
    soundLogger->set_level(spdlog::level::trace);
    fmodLogger = spdlog::stdout_color_mt("FMOD");
    fmodLogger->set_level(spdlog::level::trace);
}
