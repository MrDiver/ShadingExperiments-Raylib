// Basic Fragment Shader
#version 330

// Definition of Options
const int AMBIENT    = 1;
const int DIFFUSE    = 2;
const int SPECULAR   = 4;
const int TEXTURE    = 8;
const int FRESNEL    = 16;
const int NORMAL     = 32;
const int FOG        = 64;


in vec3 fragPosition;       // Fragment input attribute: position
in vec2 fragTexCoord;       // Fragment input attribute: texture coordinate
in vec4 fragColor;          // Fragment input attribute: color
in vec3 fragNormal;         // Fragment input attribute: normal

out vec4 finalColor;        // Fragment output: color

uniform sampler2D texture0; // Fragment input texture (always required, could be a white pixel)
uniform vec4 colDiffuse;    // Fragment input color diffuse (multiplied by texture color)
uniform int options;
uniform vec3 cameraPosition;
uniform float time;
uniform float fresnelExp;
uniform float specularExp;
uniform float fresnelStrength;
uniform float ambientStrength;

// Colors
uniform vec3 ambient_color; //0
uniform vec3 diffuse_color; //1
uniform vec3 specular_color;//2
uniform vec3 fresnel_color; //3
//                  --texture 4
//                  --normal  5
uniform float strengths[7];

vec3 lightPosition = vec3(0.0,-4.0,0.0);

void main(){
    vec3 lightDirection = normalize(lightPosition-fragPosition);
    float lightDistance = distance(fragPosition,lightPosition)/2;
    float cameraDistance = 1-min(max(distance(fragPosition,cameraPosition),1.0),strengths[6])/strengths[6];

    // Variable for additive colors    
    vec3 acc = vec3(0);

    //Ambient
    vec3 ambientPass = ambient_color*strengths[0];

    //Diffuse
    float diff = max(dot(fragNormal, lightDirection),0.0);
    vec3 diffusePass = diff*diffuse_color*strengths[1];

    //Specular
    vec3 viewDirection = normalize(cameraPosition-fragPosition);
    vec3 reflectDir = reflect(-lightDirection, fragNormal);
    float spec = pow(max(dot(viewDirection, reflectDir),0.0),specularExp);
    vec3 specularPass = spec*specular_color*strengths[2];

    //Fresnel
    vec3 vdir = normalize(fragPosition-cameraPosition);
    float viewAngle = pow((dot(vdir,fragNormal)+1),fresnelExp);
    vec3 fresnelPass = viewAngle*fresnel_color*strengths[3];

    //Texture
    vec3 texturePass = vec3(texture(texture0,fragTexCoord));


    if((options&AMBIENT)!=0)
        acc += ambientPass;
    if((options&DIFFUSE)!=0)
        acc += diffusePass;
    if((options&SPECULAR)!=0)
        acc += specularPass;
    if((options&FRESNEL)!=0)
        acc += fresnelPass;
    if((options&TEXTURE)!=0)
        acc = acc*(1-strengths[4]) + acc*texturePass*strengths[4];
    if((options&NORMAL)!=0)
        acc += vec3(fragNormal);
    if((options&FOG)!=0)
        acc = vec3(cameraDistance*acc);
    

    finalColor = vec4(acc, 1.0);
}
