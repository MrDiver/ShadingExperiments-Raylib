#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <filesystem>
namespace fs = std::filesystem;

// Include ImGui
#include "raylib_imgui.h"
using namespace rlImGui;

#include <iostream>


struct DemoTool{
    bool isOpen;
    ImVec4 col1 = WHITE;
    ImVec4 col2 = RED;
    ImVec4 col3 = BLUE;
    void draw(){
        ImGui::Begin("My First Tool", &this->isOpen, ImGuiWindowFlags_MenuBar);
        if(ImGui::BeginMenuBar()){
            /*************
             * File Menu
             *************/
            if(ImGui::BeginMenu("File")){
                if(ImGui::MenuItem("Open..","Ctrl+O")){
                    //Open File stuff here
                }
                if(ImGui::MenuItem("Save..","Ctrl+S")){
                    //Save File stuff here
                }
                if(ImGui::MenuItem("Close..","Ctrl+W")){
                    std::cout << "FUCK" << std::endl;
                    this->isOpen=false;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();

            /*
             * Tool Window
             */

            ImGui::ColorEdit4("Color3", this->col1);
            ImGui::ColorEdit4("Color4", this->col2);
            ImGui::ColorPicker3("Color3", this->col3);
            ImGui::ColorPicker4("Color4", &this->col3.x);
            ImGui::ColorButton("Press Me",col3);
        }
        ImGui::End();
    };
};

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
    DemoTool demoTool = {.isOpen = true};

    // Run Window Loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Draw
        BeginDrawing();
            ClearBackground(BLACK);

            DrawText("Hello World",100,100,20,demoTool.col3);
            DrawCircle(500,500,200,demoTool.col1);
            DrawCircle(700,500,100,demoTool.col2);


            BeginModeImGui();
                //DrawImGuiStuff
                demoTool.draw();
                if (show_demo_window)
                    ImGui::ShowDemoWindow(&show_demo_window);
            EndModeImGui();
        EndDrawing();


    }

    ShutdownImGui();
    CloseWindow();

    return 0;
}
