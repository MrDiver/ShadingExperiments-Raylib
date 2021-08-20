#pragma once

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
static void DrawTextRec(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint){}; // -- GuiTextBoxMulti()
#include "raygui.h"

const uint MAX_STRENGTHS = 7;

namespace rlg{
    typedef struct Container{
        bool ambient;
        bool diffuse;
        bool specular;
        bool texture;
        bool fresnel;
        bool normal;
        bool fog;
        Color ambientColor;
        Color diffuseColor;
        Color specularColor;
        Color fresnelColor;
        float fresnelExp;
        float specularExp;
        float strengths[MAX_STRENGTHS];
    }Container;

    enum ShaderOptions{
        AMBIENT = 1,
        DIFFUSE = 2,
        SPECULAR = 4,
        TEXURE = 8,
        FRESNEL = 16,
        NORMAL = 32,
        FOG = 64
    };

    enum StrangthValues{
        AMBIENT_STRENGTH=0,
        DIFFUSE_STRENGTH,
        SPECULAR_STRENGTH,
        FRESNEL_STRENGTH,
        TEXTURE_STRENGTH,
        NORMAL_STRENGTH,
        FOG_STRENGTH
    };


    Color V3ToC(Vector3 c){
        return (Color){(unsigned char)(c.x*255.0),(unsigned char)(c.y*255.0),(unsigned char)(c.z*255.0),255};
    }

    Vector3 CToV3(Color c){
        return (Vector3){(float)(c.r/255.0),(float)(c.g/255.0),(float)(c.b/255.0)};
    }

    typedef struct ShaderVals{
        int shaderOptions;
        Vector3 ambientColor;
        Vector3 diffuseColor;
        Vector3 specularColor;
        Vector3 fresnelColor;
        float fresnelExp;
        float specularExp;
        float strengths[MAX_STRENGTHS];
    }ShaderVals;

    ShaderVals containerToShaderVals(Container c){
        int shaderOptions = (c.ambient * rlg::AMBIENT
                      + c.diffuse * rlg::DIFFUSE
                      + c.specular* rlg::SPECULAR
                      + c.fresnel * rlg::FRESNEL
                      + c.texture * rlg::TEXURE
                      + c.normal  * rlg::NORMAL
                      + c.fog  * rlg::FOG);

        ShaderVals sv = {
            shaderOptions,
            CToV3(c.ambientColor),
            CToV3(c.diffuseColor),
            CToV3(c.specularColor),
            CToV3(c.fresnelColor),
            c.fresnelExp,
            c.specularExp,
            {0},
        };

        for(int i = 0; i < MAX_STRENGTHS; i++){
            sv.strengths[i] = c.strengths[i];
        }

        return sv;
    }

    Container initGUI(){

        Container c = (rlg::Container){
            ambient:true,
            diffuse:true,
            specular:true,
            texture:false,
            fresnel:false,
            normal:false,
            fog:false,
            ambientColor:{255,255,255,255},   
            diffuseColor:{255,255,255,255},   
            specularColor:{255,255,255,255},   
            fresnelColor:{255,255,255,255},
            fresnelExp:2.0f,
            specularExp:32.0f,
            strengths:{0,1,1,1,1,0,100}
        };
        return c;
    }

    Color GuiColorHuePanel(Rectangle r, Color c, const char* text){
        const int padding = 15;
        float hue = c.a;
        c.a = 255;
        
        Rectangle crec = {r.x+padding,r.y+padding,r.width-30-2*padding, r.height-30-2*padding};
        c = GuiColorPicker(crec,c);


        Rectangle colorRec = {r.x+padding, r.height-25,r.width-2*padding,25};
        DrawRectangleRec(colorRec,c);
        DrawRectangleLinesEx(colorRec,GuiGetStyle(0,BORDER_WIDTH),GetColor(GuiGetStyle(0,BORDER_COLOR_NORMAL)));

        GuiGroupBox(r,text);
        return c;
    }

    Container drawGUI(Container c){
        const int padding = 10;
        float ystart = 10;
        float y = 30;
        auto fy = [&y,padding](float sx,float sy){Rectangle r = {30,y,sx,sy};y+=sy+padding;return r;};
        // Checkboxes
        c.ambient = GuiCheckBox(fy(20,20),"Ambient Lighting",c.ambient);
        c.diffuse = GuiCheckBox(fy(20,20),"Diffuse Lighting",c.diffuse);
        c.specular = GuiCheckBox(fy(20,20),"Specular Lighting",c.specular);
        c.fresnel = GuiCheckBox(fy(20,20),"Fresnel Lighting",c.fresnel);
        c.texture = GuiCheckBox(fy(20,20),"Texture Mapping",c.texture);
        c.normal = GuiCheckBox(fy(20,20),"Normal Lighting",c.normal);
        c.fog = GuiCheckBox(fy(20,20),"Fog Lighting",c.fog);
        GuiGroupBox((Rectangle){10,ystart,170,y-ystart+padding+25},"Lighting Options");

        float x = 190;
        auto fx = [&x,padding](float sx,float sy){Rectangle r = {x,10,sx,sy};x+=sx+padding;return r;};
        // Color Pickers
        if(c.ambient){
            c.ambientColor = GuiColorHuePanel(fx(140,140),c.ambientColor,"Ambient Color");
        }
        if(c.diffuse){
            c.diffuseColor = GuiColorHuePanel(fx(140,140),c.diffuseColor,"Diffuse Color");
        }
        if(c.specular){
            c.specularColor = GuiColorHuePanel(fx(140,140),c.specularColor,"Specular Color");
        }
        if(c.fresnel){
            c.fresnelColor = GuiColorHuePanel(fx(140,140),c.fresnelColor,"Fresnel Color");
        }

        y+=80;
        ystart=y-20;
        if(c.ambient){
            GuiLabel(fy(10,10),TextFormat("Ambient: %.3f",c.strengths[AMBIENT_STRENGTH]));
            c.strengths[AMBIENT_STRENGTH] = GuiSlider(fy(130,30),"","",c.strengths[AMBIENT_STRENGTH],0.0,1.0);
        }
        if(c.diffuse){
            GuiLabel(fy(10,10),TextFormat("Diffuse: %.3f",c.strengths[DIFFUSE_STRENGTH]));
            c.strengths[DIFFUSE_STRENGTH] = GuiSlider(fy(130,30),"","",c.strengths[DIFFUSE_STRENGTH],0.0,1.0);
        }
        if(c.specular){
            GuiLabel(fy(10,10),TextFormat("Specular: %.3f",c.strengths[SPECULAR_STRENGTH]));
            c.strengths[SPECULAR_STRENGTH] = GuiSlider(fy(130,30),"","",c.strengths[SPECULAR_STRENGTH],0.0,1.0);

            //GuiLabel(fy(10,10),"Exponent");
            int tmp = c.specularExp;
            GuiSpinner(fy(130,20),"",&tmp,1,256,true);
            c.specularExp = Clamp((float)tmp,1,256);
        }
        if(c.fresnel){
            GuiLabel(fy(10,10),TextFormat("Fresnel: %.3f",c.strengths[FRESNEL_STRENGTH]));
            c.strengths[FRESNEL_STRENGTH] = GuiSlider(fy(130,30),"","",c.strengths[FRESNEL_STRENGTH],0.0,1.0);
            int tmp = c.fresnelExp*4;
            GuiSpinner(fy(130,20),"",&tmp,1,10,true);
            c.fresnelExp = Clamp((float)tmp,1,50)/4;
        }
        if(c.texture){
            GuiLabel(fy(10,10),TextFormat("Texture: %.3f",c.strengths[TEXTURE_STRENGTH]));
            c.strengths[TEXTURE_STRENGTH] = GuiSlider(fy(130,30),"","",c.strengths[TEXTURE_STRENGTH],0.0,1.0);
        }
        if(c.normal){
            GuiLabel(fy(10,10),TextFormat("Normal: %.3f",c.strengths[NORMAL_STRENGTH]));
            c.strengths[NORMAL_STRENGTH] = GuiSlider(fy(130,30),"","",c.strengths[NORMAL_STRENGTH],0.0,1.0);
        }
        if(c.fog){
            GuiLabel(fy(10,10),TextFormat("Fog: %.3f",c.strengths[FOG_STRENGTH]));
            c.strengths[FOG_STRENGTH] = GuiSlider(fy(130,30),"","",c.strengths[FOG_STRENGTH],0.0,100.0);
        }

        GuiGroupBox((Rectangle){10,ystart,170,y-ystart+padding+25},"Strengths");

        return c;
    }
}
