#include <RenderSystem.hpp>
#include <Logger.hpp>
#include <Components.hpp>
#include <raymath.h>

RenderSystem::RenderSystem()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetTraceLogLevel(LOG_NONE);

    InitWindow(screenWidth, screenHeight, "Portal 3 ABP Edition - Pre Alpha");

    camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 1.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FIRST_PERSON); // Set a first person camera mode

    SetTargetFPS(60);
}

void RenderSystem::AddRenderComponent(entt::entity& ent, entt::registry& reg, const std::string& modelRoute, float modelSize)
{
    RENDER_INFO("Loading {0} as a component for entity {1}", modelRoute, ent);
    Model model = LoadModel(modelRoute.c_str());
    model.transform = MatrixRotateXYZ((Vector3){ 0, DEG2RAD*180, 0 });
    reg.emplace<RenderComponent>(ent, model, modelSize);
    RENDER_TRACE("Entity {0} has registered a new Render Component", ent);
}

RenderSystem::~RenderSystem()
{
    CloseWindow();
}

void RenderSystem::Update(const entt::registry& registry)
{
    UpdateCamera(&camera);
    BeginDrawing();

        ClearBackground(SKYBLUE);
        BeginMode3D(camera);
        
            DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, BLACK); 
            DrawCube((Vector3){ -12.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BROWN);     
            DrawCube((Vector3){ 12.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BROWN);      
            DrawCube((Vector3){ 0.0f, 2.5f, 14.0f }, 32.0f, 5.0f, 1.0f, BROWN);      
            DrawCube((Vector3){ 0.0f, 2.5f, -14.0f }, 32.0f, 5.0f, 1.0f, BROWN);      

            //Para todos los elementos que tengan Render Component...
            auto view = registry.view<const RenderComponent, const PositionComponent>();
            view.each([](const auto &rcomp, const auto &p_comp){
                DrawModel(rcomp.model, (Vector3){p_comp.x, p_comp.y, p_comp.z}, rcomp.size, WHITE);
            });
        
        EndMode3D();

        DrawRectangle( 10, 10, 300, 110, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines( 10, 10, 300, 110, BLUE);
        DrawText("FMOD Demo - Control instructions:", 20, 20, 10, BLACK);
        DrawText("- Move with keys: W, A, S, D", 40, 40, 10, BLACK);
        DrawText("- Key 1: Listen to cheerful music", 40, 60, 10, BLACK);
        DrawText("- Key 2: Listen to music for ripping and tearing", 40, 80, 10, BLACK);
        DrawText("- Key 3: Have a nice chat with a friend :)", 40, 100, 10, BLACK);
            
    EndDrawing();
}

void RenderSystem::UpdatePlayerPosition(entt::entity& player, entt::entity& radio, entt::registry& reg)
{
    
    if(IsKeyPressed(KEY_ONE))
    {
        RENDER_INFO("Key pressed");
        SoundComponent comp = reg.get<SoundComponent>(radio);
        comp.floatparameers["Channel"] = 0.0f;
        reg.replace<SoundComponent>(radio, comp.event_id, comp.floatparameers, comp.intParameters, 1, comp.marked_for_play, comp.marked_for_stop);
    }

    if(IsKeyPressed(KEY_TWO))
    {
        RENDER_INFO("Key pressed");
        SoundComponent comp = reg.get<SoundComponent>(radio);
        comp.floatparameers["Channel"] = 1.0f;
        reg.replace<SoundComponent>(radio, comp.event_id, comp.floatparameers, comp.intParameters, 1, comp.marked_for_play, comp.marked_for_stop);
    }

    if(IsKeyPressed(KEY_THREE))
    {
        RENDER_INFO("Key pressed");
        SoundComponent comp = reg.get<SoundComponent>(radio);
        comp.floatparameers["Channel"] = 2.0f;
        reg.replace<SoundComponent>(radio, comp.event_id, comp.floatparameers, comp.intParameters, 1, comp.marked_for_play, comp.marked_for_stop);
    }

    reg.replace<PositionComponent>(player, camera.position.x, camera.position.y, camera.position.z);
    reg.replace<CameraComponent>(player, camera.target.x, camera.target.y, camera.target.z);
}