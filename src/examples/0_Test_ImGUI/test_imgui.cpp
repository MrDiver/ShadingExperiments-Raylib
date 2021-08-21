#include "raylib.h"
#include "raymath.h"

// Include ImGui
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <filesystem>
namespace fs = std::filesystem;

// Custom Includes
#include <functional>

typedef struct Scene{
    std::function<void()> render;
} Scene;

void shaderToTexture(Scene scene, Shader shader, RenderTexture2D buffer){
    BeginTextureMode(buffer);
        BeginShaderMode(shader);
            scene.render();
        EndShaderMode();
    EndTextureMode();
}

int main(int argc, char* argv[])
{
    // Basic Setup
    fs::current_path(fs::path(argv[0]).remove_filename());
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTraceLogLevel(LOG_WARNING);

    // Create a Fullscreen window
    InitWindow(0, 0, "Raylib Template Project");

    // Run Window Loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Draw
        BeginDrawing();
            ClearBackground(BLACK);

            DrawText("Hello World",100,100,20,WHITE);
        EndDrawing();
      
    }

    CloseWindow();

    return 0;
}
