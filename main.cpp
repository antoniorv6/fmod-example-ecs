extern "C"{
    #include "raylib.h"
}

#include "Logger.hpp"

int main(void)
{
    int a = 5;
    Logger::Init();
    CORE_WARNING("Initialized engine!");
    CORE_INFO("Cool stuff happens in sound! {0}", a);

    InitWindow(800, 450, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}