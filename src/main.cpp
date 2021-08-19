#include "raylib.h"
#include "raymath.h"

#if defined(USE_RAYGUI)
    #define RAYGUI_IMPLEMENTATION
    #define RAYGUI_SUPPORT_ICONS
    static void DrawTextRec(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint){}; // -- GuiTextBoxMulti()
    #include "raygui.h"
#endif

#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    // Basic Setup
    fs::current_path(fs::path(argv[0]).remove_filename());
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTraceLogLevel(LOG_ERROR);

    // Create a Fullscreen window
    InitWindow(0, 0, "Raylib Template Project");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
       
        //Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("TEMPLATE",GetScreenWidth()/2-100,GetScreenHeight()/2,20,DARKGRAY);
            //Just For Testing
            #if defined(USE_RAYGUI)
                GuiLabel((Rectangle){GetScreenWidth()/2-100,GetScreenHeight()/2+30,200,100},"RayGui Is Working");
            #endif
        EndDrawing();
      
    }

    CloseWindow();

    return 0;
}