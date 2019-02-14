#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"

class SpriteRenderer
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void DrawSprite(Texture &texture, glm::vec2 position,
		glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));
private:
	GLuint VAO;
	GLuint EBO;
	GLuint VBO;

	struct Vertex {
		glm::vec2 position;
		glm::vec3 color;
		glm::vec2 uv;
	};

	Vertex verts[4];

	void initRenderData();
};