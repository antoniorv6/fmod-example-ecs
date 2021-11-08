#include <RenderSystem.hpp>
#include <Logger.hpp>
#include <Components.hpp>

RenderSystem::RenderSystem()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetTraceLogLevel(LOG_NONE);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

    camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 1.0f, 12.0f };
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

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        
            DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
            DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
            DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
            DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall

            //Para todos los elementos que tengan Render Component...
            auto view = registry.view<const RenderComponent, const PositionComponent>();
            view.each([](const auto &rcomp, const auto &p_comp){
                DrawModel(rcomp.model, (Vector3){p_comp.x, p_comp.y, p_comp.z}, rcomp.size, WHITE);
            });
        
        EndMode3D();
            
    EndDrawing();
}

void RenderSystem::UpdatePlayerPosition(entt::entity& player, entt::registry& reg)
{
    reg.replace<PositionComponent>(player, camera.position.x, camera.position.y, camera.position.z);
    reg.replace<PositionComponent>(player, camera.target.x, camera.target.y, camera.target.z);
}