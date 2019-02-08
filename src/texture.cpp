#include "texture.h"
#include <SOIL.h>

Texture::Texture() {
	//Generates texture name
	glGenTextures(1, &this->ID);
}

void Texture::Generate(GLuint width, GLuint height, unsigned char* data){

	this->Width = width;
	this->Height = height;

	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

//Binds image to GL_Texture_2D
void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

