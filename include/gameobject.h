#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "texture.h"
#include "spriterenderer.h"

class GameObject {
public:
	//State
	glm::vec2 Position, Size;
	glm::vec3 Color;
	GLfloat Rotation;
	//Texture
	Texture Sprite;
	GLboolean isDestoroyed = false;
	void Draw(SpriteRenderer &renderer);

	//Constructors
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 sizem, Texture sprite, glm::vec3 color = glm::vec3(1.0f));
};