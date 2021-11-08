#include "Logger.hpp"
#include <math.h>
#include <RenderSystem.hpp>
#include <Components.hpp>
#include <SoundSystem.hpp>


int main(void)
{
    Logger::Init();

    const int MAX_COLUMNS = 20;
    // Initialization
    //--------------------------------------------------------------------------------------
    RenderSystem render = RenderSystem();
    SoundSystem soundsys = SoundSystem();
    soundsys.InitBanks("assets/fmod_banks/music_bank.bank", "assets/fmod_banks/music_bank.strings.bank");
    
    entt::registry reg;

    // -- Player creation -- //
    CORE_TRACE("Creating player entity");
    auto player = reg.create(); //Radio entity
    auto player_pos = reg.emplace<PositionComponent>(player,0.0f,0.0f,0.0f);
    auto player_cam = reg.emplace<CameraComponent>(player,  0.0f, 1.0f, 12.0f);
    reg.emplace<ListenerComponent>(player);
    
    
    CORE_INFO("Player entity created");
    // ----- //

    // -- Radio creation -- //
    CORE_TRACE("Creating radio entity");
    auto radio = reg.create(); //Radio entity
    reg.emplace<PositionComponent>(radio, 0.0f, 1.0f, 12.0f);
    render.AddRenderComponent(radio, reg, "assets/models/scene.gltf", 120.0f);
    soundsys.AddSoundComponent(radio, reg, "event:/Radio", {"Channel"}, {});
    CORE_INFO("Radio entity created");
    // ----- //

    //FMOD_ENGINE_TRACE("Loading Radio event...");
    //FMOD::Studio::EventDescription * eventDescription = nullptr;
    //ERRCHECK(m_sound_system->getEvent("event:/Radio", &eventDescription));
    //FMOD::Studio::EventInstance * soundInstance = nullptr;
    //ERRCHECK(eventDescription->createInstance(&soundInstance));
    //FMOD_3D_ATTRIBUTES l_eventAttributes {FMOD_VECTOR{0.0f, 5.0f, 12.0f}, FMOD_VECTOR{0,0,0}, FMOD_VECTOR{0,0,1}, FMOD_VECTOR{0,1,0}};
    //ERRCHECK(soundInstance->set3DAttributes(&l_eventAttributes));


    //FMOD_ENGINE_INFO("Radio loaded correctly");
    

    //ERRCHECK(soundInstance->start());

    CORE_INFO("Game inited succesfully");
    
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        //UpdateCamera(&camera);                  // Update camera
        //----------------------------------------------------------------------------------
        //FMOD_VECTOR normalizedforward =FMOD_VECTOR{-(camera.target.x - camera.position.x), camera.target.y - camera.position.y, camera.target.z - camera.position.z};
        //FMOD_VECTOR normalizedUp = FMOD_VECTOR{camera.up.x, camera.up.y, camera.up.z};

        //float angz = angle(normalizedforward, {0,0,1});
        //float angx = angle(normalizedforward, {1,0,0});

        //FMOD_3D_ATTRIBUTES l_listenerAttributes {FMOD_VECTOR{-camera.position.x, camera.position.y, camera.position.z}, FMOD_VECTOR{0,0,0}, {cos(angx), 0, sin(angx)}, {0,1,0}};
        //ERRCHECK(m_sound_system->setListenerAttributes(0, &l_listenerAttributes));
        //m_sound_system->update();
        
        // Draw
        //----------------------------------------------------------------------------------
        render.Update(reg);
        render.UpdatePlayerPosition(player, radio, reg);
        
        soundsys.Update(reg);
        //----------------------------------------------------------------------------------
    }

    CORE_INFO("Game closed successfully");

    return 0;
}