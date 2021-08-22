#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <filesystem>
namespace fs = std::filesystem;

// Include ImGui
#include "raylib_imgui.h"
using namespace rlImGui;

int main(int argc, char* argv[])
{
    // Basic Setup
    fs::current_path(fs::path(argv[0]).remove_filename());
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTraceLogLevel(LOG_WARNING);

    // Create a Fullscreen window
    InitWindow(0, 0, "Raylib Template Project");
    ImGuiIO& io = InitImGui();

    bool show_demo_window = true;

    // Run Window Loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Draw
        BeginDrawing();
            ClearBackground(BLACK);

            DrawText("Hello World",100,100,20,WHITE);
            DrawCircle(500,500,200,GRAY);

            BeginModeImGui();
                //DrawImGuiStuff
                if (show_demo_window)
                    ImGui::ShowDemoWindow(&show_demo_window);
            EndModeImGui();


            DrawText("Im Over ImGUI WUUUUU",500,100,20,WHITE);

        EndDrawing();
    }

    ShutdownImGui();
    CloseWindow();

    return 0;
}
