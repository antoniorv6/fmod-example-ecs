#pragma once

#include <memory>
#include <spdlog/spdlog.h>

class Logger
{
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return coreLogger;}
        inline static std::shared_ptr<spdlog::logger>& GetSoundLogger() {return soundLogger;}
        inline static std::shared_ptr<spdlog::logger>& GetFMODLogger() {return fmodLogger;}

    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> soundLogger;
        static std::shared_ptr<spdlog::logger> fmodLogger;

};

// Core logging
#define CORE_TRACE(...) ::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...) ::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARNING(...) ::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...) ::Logger::GetCoreLogger()->error(__VA_ARGS__)

// Sound engine logging
#define SOUND_TRACE(...) ::Logger::GetSoundLogger()->trace(__VA_ARGS__)
#define SOUND_INFO(...) ::Logger::GetSoundLogger()->info(__VA_ARGS__)
#define SOUND_WARNING(...) ::Logger::GetSoundLogger()->warn(__VA_ARGS__)
#define SOUND_ERROR(...) ::Logger::GetSoundLogger()->error(__VA_ARGS__)

//FMOD logger
#define FMOD_ENGINE_TRACE(...) ::Logger::GetFMODLogger()->trace(__VA_ARGS__)
#define FMOD_ENGINE_INFO(...) ::Logger::GetFMODLogger()->info(__VA_ARGS__)
#define FMOD_ENGINE_WARNING(...) ::Logger::GetFMODLogger()->warn(__VA_ARGS__)
#define FMOD_ENGINE_ERROR(...) ::Logger::GetFMODLogger()->error(__VA_ARGS__)
#define FMOD_ENGINE_CRITICAL(...) ::Logger::GetFMODLogger()->critical(__VA_ARGS__)