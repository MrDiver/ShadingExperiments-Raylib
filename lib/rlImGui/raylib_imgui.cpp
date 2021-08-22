
#include "raylib_imgui.h"

namespace rlImGui{

    void InitImGui(int glsl_version){
        //Setup ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        GLFWwindow* window = (GLFWwindow*) glfwGetCurrentContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(TextFormat("#version %i",glsl_version));
    }

    void BeginModeImGui(){
        //rlDrawRenderBatchActive();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void EndModeImGui(){
        ImGui::Render();
        ImDrawData* drawData = ImGui::GetDrawData();
        rlDrawRenderBatchActive();
        ImGui_ImplOpenGL3_RenderDrawData(drawData);
    }

    void ShutdownImGui(){
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}

namespace rlImGui{
//     bool ColorEdit3(const char* label, ImVec4& col, ImGuiColorEditFlags flags)
//     {
//         float c[3] = {col.x,col.y,col.z};
//         bool res = ImGui::ColorEdit3(label, c, flags);
//         col.x = c[0];
//         col.y = c[1];
//         col.z = c[2];
//         return res;
//     }
//
//     bool ColorEdit4(const char* label, ImVec4& col, ImGuiColorEditFlags flags)
//     {
//         float c[4] = {col.x,col.y,col.z,col.w};
//         bool res = ImGui::ColorEdit3(label, c, flags);
//         col.x = c[0];
//         col.y = c[1];
//         col.z = c[2];
//         col.w = c[3];
//         return res;
//     }
//
//     bool ColorPicker3(const char* label, ImVec4& col, ImGuiColorEditFlags flags)
//     {
//         float c[3] = {col.x,col.y,col.z};
//         bool res = ImGui::ColorPicker3(label, c, flags);
//         col.x = c[0];
//         col.y = c[1];
//         col.z = c[2];
//         return res;
//     }
//
//     bool ColorPicker4(const char* label, ImVec4& col, ImGuiColorEditFlags flags, const float* ref_col){
//         float c[4] = {col.x,col.y,col.z,col.w};
//         bool res = ImGui::ColorPicker4(label, c, flags, ref_col);
//         col.x = c[0];
//         col.y = c[1];
//         col.z = c[2];
//         col.w = c[3];
//         return res;
//     };
}
