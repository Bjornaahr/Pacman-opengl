#include "spriterenderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




SpriteRenderer::SpriteRenderer()
{
	this->initRenderData();
}



void SpriteRenderer::initRenderData()
{

	verts[0] = { Vertex{ /*pos*/{ 0.5f, 1.0f }, /*col*/{ 1, 0, 0 }, /*uv*/{ 0.00f, 0.00f } } };
	verts[1] = { Vertex{ /*pos*/{ 1.0f, 1.0f }, /*col*/{ 0, 1, 0 }, /*uv*/{ 0.25f, 0.00f } } };
	verts[2] = { Vertex{ /*pos*/{ 1.0f, 0.5f }, /*col*/{ 0, 0, 1 }, /*uv*/{ 0.25f, 0.25f } } };
	verts[3] = { Vertex{ /*pos*/{ 0.5f, 0.5f }, /*col*/{ 1, 1, 1 }, /*uv*/{ 0.00f, 0.25f } } };

	glBindVertexArray(this->VAO);

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);


	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3 * 2, NULL, GL_DYNAMIC_DRAW);
}



void SpriteRenderer::DrawSprite(Texture &texture, glm::vec2 position,
	glm::vec2 size, GLfloat rotate, glm::vec3 color)
{

	

	//Just have to add transformation

	


	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0

	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(elements), elements);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const GLvoid*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}