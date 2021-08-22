#ifndef RAYLIB_IMGUI
#define RAYLIB_IMGUI

#include "raylib.h"
#include "rlgl.h"

#define IM_VEC2_CLASS_EXTRA ImVec2(const Vector2& v) { x=v.x; y=v.y; };\
                            operator Vector2() const{return (Vector2){x,y};};

#define IM_VEC4_CLASS_EXTRA ImVec4(const Vector4& v) { x=v.x; y=v.y; z=v.z; w=v.w; };\
                            ImVec4(const Color& c) {x=c.r/255.f; y=c.g/255.f;z=c.b/255.f;w=c.a/255.f;};\
                            operator Vector4() const{return (Vector4){x,y,z,w}; };\
                            operator Color() const{return (Color){(unsigned char)(x*255.f),(unsigned char)(y*255.f),(unsigned char)(z*255.f),(unsigned char)(w*255.f)}; };\
                            operator float*() {return &x;};

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

namespace rlImGui{
    //raylib compat functions
    void InitImGui(int glsl_version=330); // Starts an ImGui context should be called after raylibs InitWindow()
    void BeginModeImGui();                // Starts the ImGui DrawMode should be called after raylibs BeginDraw()
    void EndModeImGui();                  // Ends the ImGui DrawMode should before raylibs EndDraw()
    void ShutdownImGui();                 // Shutdown ImGui should be called before raylibs CloseWindow()

    //ImGui Compat Components for raylib
//     bool ColorEdit3(const char* label, ImVec4& col, ImGuiColorEditFlags flags = 0);
//     bool ColorEdit4(const char* label, ImVec4& col, ImGuiColorEditFlags flags = 0);
//     bool ColorPicker3(const char* label, ImVec4& col, ImGuiColorEditFlags flags = 0);
//     bool ColorPicker4(const char* label, ImVec4& col, ImGuiColorEditFlags flags = 0, const float* ref_col = NULL);
}

#endif
