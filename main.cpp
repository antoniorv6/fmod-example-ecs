extern "C"{
    #include "raylib.h"
}

#include <entt/entity/registry.hpp>
#include "Logger.hpp"
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <math.h>

void ERRCHECK_FMOD (FMOD_RESULT result, const char * file, int line)
{
	if(result != FMOD_OK)
	{
        FMOD_ENGINE_CRITICAL("{0} - {1}", result, FMOD_ErrorString(result));
		exit(-1);
	}
}
#define ERRCHECK(_result) ERRCHECK_FMOD(_result, __FILE__, __LINE__)

FMOD::Studio::System * m_sound_system = nullptr; 
FMOD::System * m_low_level_system = nullptr; 
FMOD::Studio::Bank* m_masterBank = nullptr;
FMOD::Studio::Bank* m_stringBank = nullptr;

void init_FMOD()
{
    FMOD_ENGINE_TRACE("Initializing FMOD engine in our game...");
    ERRCHECK(FMOD::Studio::System::create(&m_sound_system));
    ERRCHECK(m_sound_system->getCoreSystem(&m_low_level_system));
    ERRCHECK(m_low_level_system->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
    ERRCHECK(m_low_level_system->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
    ERRCHECK(m_sound_system->initialize(512, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_NORMAL, 0));
    FMOD_ENGINE_INFO("Successfully initialized FMOD engine");
}

void load_FMOD_banks()
{
    FMOD_ENGINE_TRACE("Initializing FMOD engine in our game...");
    ERRCHECK(m_sound_system->loadBankFile("assets/fmod_banks/music_bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_masterBank));
    ERRCHECK(m_sound_system->loadBankFile("assets/fmod_banks/music_bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_stringBank));
    FMOD_ENGINE_INFO("Successfully loaded FMOD banks");
}

FMOD_VECTOR normalizeVec(FMOD_VECTOR unnormalized)
{
    float modulus = sqrt(unnormalized.x * unnormalized.x + unnormalized.y * unnormalized.y + unnormalized.z * unnormalized.z);
    return FMOD_VECTOR{unnormalized.x / modulus, unnormalized.y / modulus, unnormalized.z / modulus};
}

float angle(FMOD_VECTOR forward, FMOD_VECTOR up)
{
    float dot = forward.x*up.x + forward.y*up.y + forward.z*up.z;
    float lenSq1 = forward.x*forward.x + forward.y*forward.y + forward.z*forward.z;
    float lenSq2 = up.x*up.x + up.y*up.y + up.z*up.z;
    return acos(dot/sqrt(lenSq1 * lenSq2));
}

int main(void)
{
    Logger::Init();

    init_FMOD();

    load_FMOD_banks();

    const int MAX_COLUMNS = 20;
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetTraceLogLevel(LOG_NONE);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 1.0f, 12.0f };
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

    FMOD_ENGINE_TRACE("Loading Radio event...");
    FMOD::Studio::EventDescription * eventDescription = nullptr;
    ERRCHECK(m_sound_system->getEvent("event:/Radio", &eventDescription));
    FMOD::Studio::EventInstance * soundInstance = nullptr;
    ERRCHECK(eventDescription->createInstance(&soundInstance));
    FMOD_3D_ATTRIBUTES l_eventAttributes {FMOD_VECTOR{0.0f, 0.0f, 12.0f}, FMOD_VECTOR{0,0,0}, FMOD_VECTOR{0,0,1}, FMOD_VECTOR{0,1,0}};
    ERRCHECK(soundInstance->set3DAttributes(&l_eventAttributes));


    FMOD_ENGINE_INFO("Radio loaded correctly");
    

    ERRCHECK(soundInstance->start());

    CORE_INFO("Game inited succesfully");
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);                  // Update camera
        //----------------------------------------------------------------------------------
        FMOD_VECTOR normalizedforward =FMOD_VECTOR{-(camera.target.x - camera.position.x), camera.target.y - camera.position.y, camera.target.z - camera.position.z};
        FMOD_VECTOR normalizedUp = FMOD_VECTOR{camera.up.x, camera.up.y, camera.up.z};

        float ang = angle(normalizedforward, {0,0,1});

        FMOD_3D_ATTRIBUTES l_listenerAttributes {FMOD_VECTOR{-camera.position.x, camera.position.y, camera.position.z}, FMOD_VECTOR{0,0,0}, {-cos(ang), 0, -sin(ang)}, {0,1,0}};
        ERRCHECK(m_sound_system->setListenerAttributes(0, &l_listenerAttributes));
        //ERRCHECK(soundInstance->set3DAttributes(&l_eventAttributes));
        m_sound_system->update();
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
                DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
                DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
                DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall

                DrawCube((Vector3){ 0.0f, 1.f, 12.0f }, 2.0f, 2.0f, 2.0f, RED);      // Draw a yellow wall

            EndMode3D();
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    FMOD_ENGINE_TRACE("Dropping FMOD...");
    eventDescription->releaseAllInstances();
    soundInstance->release();
    m_masterBank->unload();
    m_stringBank->unload();
    FMOD_ENGINE_INFO("FMOD dropped");

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    CORE_INFO("Game closed successfully");

    return 0;
}