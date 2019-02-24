#include "texture.h"
#include <SOIL.h>

Texture::Texture() {
	//Generates texture name
	glGenTextures(1, &this->ID);
}

//Generates and binds texture
void Texture::Generate(GLuint width, GLuint height, unsigned char* data){

	this->Width = width;
	this->Height = height;

	//Binds texture to this object
	glBindTexture(GL_TEXTURE_2D, this->ID);
	//Texture image, this makes the shader able to read it
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//Set all texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Unbinds texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

//Binds texture
void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

