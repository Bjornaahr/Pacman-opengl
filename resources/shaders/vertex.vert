#version 330 core

//layout (location = 0) in vec4 vertex;

in vec4 position;
in vec3 color;
in vec2 texcoord;
out vec3 Color;
out vec2 Texcoord;

uniform mat4 model      =mat4(1);
uniform mat4 view       =mat4(1);                         //<-- 4x4 Transformation Matrices
uniform mat4 projection =mat4(1);

void main()
{
    Color = color;
    Texcoord = texcoord;
	gl_Position = projection * view * model * position; 
	
	}
