extern "C"{
    #include "raylib.h"
}

#include <entt/entity/registry.hpp>
#include "Logger.hpp"
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>

void ERRCHECK_FMOD (FMOD_RESULT result, const char * file, int line)
{
	if(result != FMOD_OK)
	{
        FMOD_ENGINE_ERROR("{0} - {1}", result, FMOD_ErrorString(result));
		exit(-1);
	}
}
#define ERRCHECK(_result) ERRCHECK_FMOD(_result, __FILE__, __LINE__)

void init_FMOD()
{
    FMOD::Studio::System * m_sound_system = nullptr; 
    FMOD::System * m_low_level_system = nullptr; 

    ERRCHECK(FMOD::Studio::System::create(&m_sound_system));
    ERRCHECK(m_sound_system->getCoreSystem(&m_low_level_system));
    ERRCHECK(m_sound_system->initialize(512, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_3D_RIGHTHANDED, 0));
    //ERRCHECK(m_low_level_system->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
	//ERRCHECK(m_low_level_system->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
}


int main(void)
{
    Logger::Init();

    init_FMOD();

    const int MAX_COLUMNS = 20;
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetTraceLogLevel(LOG_NONE);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 4.0f, 2.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Generates some random columns
    float heights[MAX_COLUMNS] = { 0 };
    Vector3 positions[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12);
        positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), heights[i]/2.0f, (float)GetRandomValue(-15, 15) };
        colors[i] = (Color){ GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
    }

    SetCameraMode(camera, CAMERA_FIRST_PERSON); // Set a first person camera mode

    SetTargetFPS(60);
    CORE_INFO("Game inited succesfully");
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);                  // Update camera
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
                DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
                DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
                DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall

            EndMode3D();
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    CORE_INFO("Game closed successfully");

    return 0;
}