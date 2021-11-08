#pragma once

#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <string>
#include <map>
#include <entt/entt.hpp>

class SoundSystem
{
    private:
        std::map<std::string, FMOD::Studio::EventDescription*> eventMap;
        std::map<std::string, FMOD::Studio::EventInstance*> eventInstances;
        FMOD::Studio::System * soundSystem;
        FMOD::System* low_level_system;
        FMOD::Studio::Bank* master_bank;
        FMOD::Studio::Bank* strings_bank;
    
    public:
        SoundSystem();
        ~SoundSystem();

        void InitBanks(const std::string& master_bank_location, const std::string& strings_bank_location);
        void AddSoundComponent(entt::entity& ent, entt::registry& reg, const std::string& eventName, std::vector<std::string> floatvars, std::vector<std::string> intvars);
        void Update(entt::registry& reg);
};