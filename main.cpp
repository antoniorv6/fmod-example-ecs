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

    CORE_TRACE("Creating game entities");

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
    reg.emplace<PositionComponent>(radio, 0.0f, 1.95f, 12.0f);
    render.AddRenderComponent(radio, reg, "assets/models/radio/scene.gltf", 120.0f);
    soundsys.AddSoundComponent(radio, reg, "event:/Radio", {"Channel"}, {});
    CORE_INFO("Radio entity created");
    // ----- //

    // -- Table creation -- //
    CORE_TRACE("Creating table entity");
    auto table = reg.create(); //Radio entity
    reg.emplace<PositionComponent>(table, 0.0f, 0.0f, 12.0f);
    render.AddRenderComponent(table, reg, "assets/models/table/scene.gltf", 0.01f);
    CORE_INFO("Table entity created");
    // ----- //

    // -- Table creation -- //
    CORE_TRACE("Creating toilet entity");
    auto toilet = reg.create(); //Radio entity
    reg.emplace<PositionComponent>(toilet, 4.0f, 0.0f, 12.0f);
    render.AddRenderComponent(toilet, reg, "assets/models/toilet/scene.gltf", 2.0f);
    CORE_INFO("Toilet entity created");
    // ----- //

    // -- Table creation -- //
    CORE_TRACE("Creating bed entity");
    auto bed = reg.create(); //Radio entity
    reg.emplace<PositionComponent>(bed, -2.0f, 0.0f, 6.0f);
    render.AddRenderComponent(bed, reg, "assets/models/bed/scene.gltf", 1.0f);
    CORE_INFO("Bed entity created");
    // ----- //


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