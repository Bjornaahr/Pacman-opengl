#version 330 core

in vec3 Color;
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D texOne;
uniform sampler2D texTwo;
void main()
 {
	outColor = texture(texOne, Texcoord) * vec4(Color, 1); 
 }
