#version 330 core

layout (location = 0) in vec4 vertex;

in vec3 color;
out vec3 Color;
out vec2 Texcoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    Color = color;
    Texcoord = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
 }