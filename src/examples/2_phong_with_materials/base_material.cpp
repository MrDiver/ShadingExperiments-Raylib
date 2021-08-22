#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <filesystem>
namespace fs = std::filesystem;


// Include ImGui
#include "raylib_imgui.h"
using namespace rlImGui;
#include "GUI/Gui.h"

#include <iostream>

int main(int argc, char* argv[])
{
    // Basic Setup
    fs::current_path(fs::path(argv[0]).remove_filename());
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTraceLogLevel(LOG_WARNING);

    // Create a Fullscreen window
    InitWindow(0, 0, "Raylib Template Project");
    InitImGui();

    bool show_demo_window = true;
    MaterialGui mg;
    LightGui lg;

    // Run Window Loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Draw
        BeginDrawing();
            ClearBackground(BLACK);

            const int offset = 40;
            int start = GetScreenWidth()/2-(offset/2)*lg.lights.size();
            for(int i = 0; i < lg.lights.size(); i++){
                Light l = lg.lights.at(i);
                DrawCircle(start+i*offset,100,15,l.ambient);
                DrawCircle(start+i*offset,100,10,l.diffuse);
                DrawCircle(start+i*offset,100,5,l.specular);
            }

            BeginModeImGui();
                //DrawImGuiStuff
                mg.draw();
                lg.draw();
            EndModeImGui();
        EndDrawing();


    }

    ShutdownImGui();
    CloseWindow();

    return 0;
}
