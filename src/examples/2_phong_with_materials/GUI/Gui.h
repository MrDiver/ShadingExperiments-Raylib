#pragma once

#include <vector>

typedef struct MaterialGui{
    bool isOpen = true;
    ImVec4 ambient = WHITE;
    ImVec4 diffuse = WHITE;
    ImVec4 specular = WHITE;
    bool init = true;

    void _picker_group(const char* title, ImVec4& var){
        if(init) ImGui::SetNextTreeNodeOpen(true);
        ImGui::BeginChild("",{250,0});
        if(ImGui::TreeNode(title)){
            ImGui::ColorPicker3("a",var, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_HDR);
            ImGui::Text("Strength");
            ImGui::SliderFloat(" ",&var.w,0.0,1.0);
            ImGui::TreePop();
        }
        ImGui::Separator();
        ImGui::EndChild();
    }
    void draw(){
        if(init){
            ImGui::SetNextWindowPos({0,0});
            ImGui::SetNextWindowSize({GetScreenWidth()*0.15f,(float)GetScreenHeight()/2});
        }
        ImGui::Begin("Material",&isOpen);
            _picker_group("Ambient",ambient);
            _picker_group("Diffuse",diffuse);
            _picker_group("Specular",specular);
        ImGui::End();
        if(init)
            init = false;
    };
}MaterialGui;

typedef struct Light{
    ImVec2 pos = {0,0};
    ImVec4 ambient = WHITE;
    ImVec4 diffuse = WHITE;
    ImVec4 specular = WHITE;
}Light;

typedef struct LightGui{
    bool isOpen = true;
    std::vector<Light> lights;
    bool init = true;

    void _picker_group(const char* title, ImVec4& var){
        if(init) ImGui::SetNextTreeNodeOpen(true);
        if(ImGui::TreeNode(title)){
            ImGui::BeginChild("CP",{ImGui::GetWindowWidth(),ImGui::GetWindowWidth()*0.7f});
            ImGui::ColorPicker3("a",var, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_Float |
            ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_HDR);
            ImGui::EndChild();
            ImGui::Text("Strength");
            ImGui::SliderFloat(" ",&var.w,0.0,1.0);
            ImGui::TreePop();
        }
        ImGui::Separator();
    }
    void draw(){
        if(init){
            ImGui::SetNextWindowPos({GetScreenWidth()*0.85f,0});
            ImGui::SetNextWindowSize({GetScreenWidth()*0.15f,(float)GetScreenHeight()/2});
        }

        ImGui::Begin("Light",&isOpen);
            ImGui::Value("Lights: ",(int)lights.size());
            ImGui::SameLine();
            if(ImGui::Button("Add Light"))
            {
                lights.push_back({});
            }

            for(auto l = lights.begin(); l!=lights.end(); l=std::next(l)){
//                 Light* l = &lights.at(i);
                int i = l-lights.begin();
                if(ImGui::TreeNode(TextFormat("Light #%i",i))){
                    ImGui::DragFloat2("Position",&l->pos.x,0.1,-10,10,"%.2f");
                    _picker_group("Ambient",l->ambient);
                    _picker_group("Diffuse",l->diffuse);
                    _picker_group("Specular",l->specular);
                    if(ImGui::Button(TextFormat("Delete Light #%i",i))){
                        lights.erase(l);
                    }
                    ImGui::TreePop();
                }else
                {
                    ImGui::ColorButton("Ambient",l->ambient);ImGui::SameLine();
                    ImGui::ColorButton("Diffuse",l->diffuse);ImGui::SameLine();
                    ImGui::ColorButton("Specular",l->specular);ImGui::SameLine();
                    if(ImGui::Button(TextFormat("Delete Light #%i",i))){
                        lights.erase(l);
                        break;
                    }
                    ImGui::Separator();
                }
            }

        ImGui::End();
        if(init)
            init = false;
    };
}LightGui;
