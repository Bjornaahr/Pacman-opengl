#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "texture.h"

class GameObject {
public:
	//State
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	GLfloat Rotation;
	//Texture
	Texture Sprite;
	//Constructors
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 sizem, Texture sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f,0.0f));
};