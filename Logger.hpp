#pragma once

#include <memory>
#include <spdlog/spdlog.h>

class Logger
{
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return coreLogger;}
        inline static std::shared_ptr<spdlog::logger>& GetSoundLogger() {return soundLogger;}
        inline static std::shared_ptr<spdlog::logger>& GetRenderLogger() {return renderLogger;}


    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> soundLogger;
        static std::shared_ptr<spdlog::logger> renderLogger;

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

//Render Logger
#define RENDER_TRACE(...) ::Logger::GetRenderLogger()->trace(__VA_ARGS__)
#define RENDER_INFO(...) ::Logger::GetRenderLogger()->info(__VA_ARGS__)
#define RENDER_WARNING(...) ::Logger::GetRenderLogger()->warn(__VA_ARGS__)
#define RENDER_ERROR(...) ::Logger::GetRenderLogger()->error(__VA_ARGS__)