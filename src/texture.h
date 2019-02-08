#pragma once
#include <GL/glew.h>

class Texture {
public:
	//Refrence to texture object
	GLuint ID;
	//Dimensions of texture
	GLuint Width, Height;

	Texture();
	//Generate texure from data
	void Generate(GLuint width, GLuint height, unsigned char* data);
	//Binds texture to active GL_TEXTURE_2D object
	void Bind() const;


};