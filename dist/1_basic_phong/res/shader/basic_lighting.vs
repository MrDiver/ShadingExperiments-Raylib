// Basic Vertex Shader
#version 330

in vec3 vertexPosition;     // Vertex input attribute: position
in vec2 vertexTexCoord;     // Vertex input attribute: texture coordinate
in vec4 vertexColor;        // Vertex input attribute: color
in vec3 vertexNormal;       // Vertex input attribute: normal

out vec3 fragPosition;      // To-fragment attribute: position
out vec2 fragTexCoord;      // To-fragment attribute: texture coordinate
out vec4 fragColor;         // To-fragment attribute: color
out vec3 fragNormal;        // To-fragment attribute: normal

uniform mat4 mvp;           // Model-View-Projection matrix
uniform mat4 matModel;      // VS: Model matrix
uniform mat4 matNormal;     // VS: Normal matrix
uniform mat4 projection;    // VS: Projection matrix
uniform mat4 view;          // VS: View matrix

void main(){
    fragPosition = vec3(matModel*vec4(vertexPosition,1.0));
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    fragNormal = normalize(vec3(matNormal*vec4(vertexNormal,1.0)));

    gl_Position = mvp*vec4(vertexPosition,1.0);
}
