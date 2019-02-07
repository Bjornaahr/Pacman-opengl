#version 150

in vec3 Color;
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D texOne;
uniform sampler2D texTwo;
void main()
 {
	outColor = texture(texOne, Texcoord); 
 }