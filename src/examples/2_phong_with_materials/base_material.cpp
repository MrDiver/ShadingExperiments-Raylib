#include "raylib.h"
#include "raymath.h"

#include <filesystem>
namespace fs = std::filesystem;

// Custom Includes
#include "GUI/GuiMain.h"
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
    rlg::Container c = rlg::initGUI();

    // Create Shaders and buffers
    Shader basic_shader = LoadShader("res/shader/basic_lighting.vs","res/shader/phong.fs");
    // basic_shader.locs[SHADER_LOC_VERTEX_POSITION] = GetShaderLocationAttrib(basic_shader,"vertexPosition");
    // basic_shader.locs[SHADER_LOC_VERTEX_TEXCOORD01] = GetShaderLocationAttrib(basic_shader,"vertexTexCoord");
    // basic_shader.locs[SHADER_LOC_VERTEX_COLOR] = GetShaderLocationAttrib(basic_shader,"vertexColor");
    // basic_shader.locs[SHADER_LOC_VERTEX_NORMAL] = GetShaderLocationAttrib(basic_shader,"vertexNormal");
    basic_shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(basic_shader, "cameraPosition");
    basic_shader.locs[SHADER_LOC_COLOR_AMBIENT] = GetShaderLocation(basic_shader, "ambient_color");
    basic_shader.locs[SHADER_LOC_COLOR_DIFFUSE] = GetShaderLocation(basic_shader, "diffuse_color");
    basic_shader.locs[SHADER_LOC_COLOR_SPECULAR] = GetShaderLocation(basic_shader, "specular_color");
    const int shaderFresnelColorLoc = GetShaderLocation(basic_shader, "fresnel_color");
    const int shaderOptionsLoc = GetShaderLocation(basic_shader, "options");
    const int shaderTimeLoc = GetShaderLocation(basic_shader, "time");
    const int shaderFresnelExpLoc = GetShaderLocation(basic_shader, "fresnelExp");
    const int shaderSpecularExpLoc = GetShaderLocation(basic_shader, "specularExp");
    const int shaderStrengthsLoc = GetShaderLocation(basic_shader, "strengths");
    float fresnelExp = 3.0f;
    SetShaderValue(basic_shader,shaderFresnelExpLoc,&fresnelExp,SHADER_UNIFORM_FLOAT);

    uint shaderOptions = 0x0u;

    //Render Buffers
    RenderTexture buffer = LoadRenderTexture(GetScreenWidth(),GetScreenHeight());
    RenderTexture ambient_buffer = LoadRenderTexture(GetScreenWidth(),GetScreenHeight());

    //Gen Textures
    Image checker = GenImageChecked(1024,1024,100,100,BLACK,WHITE);
    Texture2D checkerTexture = LoadTextureFromImage(checker);
    UnloadImage(checker);

    //Load Models
    Model sphere = LoadModelFromMesh(GenMeshSphere(1.0f,40,40));
    sphere.materials->shader=basic_shader;
    sphere.materials->maps->texture=checkerTexture;

    Model plane = LoadModelFromMesh(GenMeshCube(100,0.1,100));
    plane.materials->shader=basic_shader;
    plane.materials->maps->texture=checkerTexture;

    Model torus = LoadModelFromMesh(GenMeshTorus(0.4,1.0,20,80));
    torus.materials->shader=basic_shader;
    torus.materials->maps->texture=checkerTexture;

    // Setup Scene
    Camera3D cam = {
        position:{0.0f,-5.0f,10.0f},
        target:{0.0f,0.0f,0.0f},
        up:{0.0f,1.0f,0.0f},
        fovy:45.0f,
        projection: CAMERA_PERSPECTIVE
    };
    SetCameraMode(cam,CAMERA_ORBITAL);

    Scene basic_scene = (Scene){
        [&cam,sphere,plane](){
            BeginMode3D(cam);
                ClearBackground(BLACK);
                DrawModel(plane,{0.0,2.0,0.0},1.0f,WHITE);
                DrawModel(sphere,Vector3Zero(),1.0f,WHITE);
                DrawModel(sphere,{5.0f,0.0f,0.0f},0.5f,WHITE);
                DrawModel(sphere,{-5.0f,0.0f,0.0f},0.5f,WHITE);
                DrawModel(sphere,{0.0f,0.0f,5.0f},0.5f,WHITE);
                DrawModel(sphere,{0.0f,0.0f,-5.0f},0.5f,WHITE);
                DrawModel(sphere,{10.0f,0.0f,-10.0f},0.5f,WHITE);
                DrawModel(sphere,{-10.0f,0.0f,10.0f},0.5f,WHITE);
                DrawModel(sphere,{-10.0f,0.0f,-10.0f},0.5f,WHITE);
                DrawModel(sphere,{10.0f,0.0f,10.0f},0.5f,WHITE);
            EndMode3D();
        }
    };


    float time = GetTime();
    Scene cube_scene = (Scene){
        [&cam,sphere,plane,torus,&time](){
            BeginMode3D(cam);
                ClearBackground(BLACK);
                DrawModel(plane,{0.0,2.0,0.0},1.0f,WHITE);
                DrawModelEx(torus,{0.0,0.0,0.0},{1.0f,1.0f,0.0f},time*80,{1.0f,1.0f,1.0f},WHITE);
                DrawModelEx(torus,{-4.0,0.0,0.0},{1.0f,0.0f,0.0f},time*100,{1.0f,1.0f,1.0f},WHITE);
                DrawModelEx(torus,{-7.0,0.0,0.0},{1.0f,1.0f,-10.0f},time*85,{1.0f,1.0f,1.0f},WHITE);
                DrawModelEx(torus,{-10.0,0.0,0.0},{1.0f,-1.0f,0.0f},time*100,{1.0f,1.0f,1.0f},WHITE);
                DrawModelEx(torus,{4.0,0.0,0.0},{-1.0f,1.0f,0.0f},time*90,{1.0f,1.0f,1.0f},WHITE);
                DrawModelEx(torus,{7.0,0.0,0.0},{1.0f,1.0f,0.0f},time*100,{1.0f,1.0f,1.0f},WHITE);
                DrawModelEx(torus,{10.0,0.0,0.0},{1.0f,1.0f,0.0f},time*70,{1.0f,1.0f,1.0f},WHITE);
            EndMode3D();
        }
    };

    // Run Window Loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        time = GetTime();
        UpdateCamera(&cam);
        SetShaderValue(basic_shader,shaderTimeLoc,&time,SHADER_UNIFORM_FLOAT);
        SetShaderValue(basic_shader,basic_shader.locs[SHADER_LOC_VECTOR_VIEW],&cam.position.x,SHADER_UNIFORM_VEC3);

        //UpdateShaderValues
        
        rlg::ShaderVals sv = rlg::containerToShaderVals(c);
        //float tmp = sv.strengths;
        SetShaderValue(basic_shader, shaderOptionsLoc, &sv.shaderOptions, SHADER_UNIFORM_INT);
        SetShaderValue(basic_shader,basic_shader.locs[SHADER_LOC_COLOR_AMBIENT], &sv.ambientColor.x, SHADER_UNIFORM_VEC3);
        SetShaderValue(basic_shader,basic_shader.locs[SHADER_LOC_COLOR_DIFFUSE], &sv.diffuseColor.x, SHADER_UNIFORM_VEC3);
        SetShaderValue(basic_shader,basic_shader.locs[SHADER_LOC_COLOR_SPECULAR], &sv.specularColor.x, SHADER_UNIFORM_VEC3);
        SetShaderValue(basic_shader,shaderFresnelColorLoc, &sv.fresnelColor.x, SHADER_UNIFORM_VEC3);
        SetShaderValue(basic_shader,shaderFresnelExpLoc, &sv.fresnelExp, SHADER_UNIFORM_FLOAT);
        SetShaderValue(basic_shader,shaderSpecularExpLoc, &sv.specularExp, SHADER_UNIFORM_FLOAT);
        SetShaderValueV(basic_shader,shaderStrengthsLoc, &sv.strengths[0], SHADER_UNIFORM_FLOAT, 7);
        
        shaderToTexture(cube_scene,basic_shader,buffer);
       
        //Draw
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(buffer.texture,0,0,WHITE);

            c = rlg::drawGUI(c);

            DrawText(TextFormat("Time: %f",time),10,GetScreenHeight()-50,20,LIME);
            //DrawText(TextFormat("x:%f y:%f z:%f",cam.position.x,cam.position.y,cam.position.z),150,GetScreenHeight()-50,20,LIME);
            //DrawText(TextFormat("%i",sv.shaderOptions),500,800,20,LIME);
        EndDrawing();
      
    }

    UnloadShader(basic_shader);
    UnloadRenderTexture(buffer);
    UnloadTexture(checkerTexture);
    UnloadModel(sphere);
    UnloadModel(plane);
    UnloadModel(torus);
    CloseWindow();

    return 0;
}
