#include "spriterenderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaderloader.h"

#define PI (float)3.14159265359


ShaderProgram activeShaderProgram;



SpriteRenderer::SpriteRenderer()
{
	this->initRenderData();
}



void SpriteRenderer::initRenderData()
{

	verts[0] = { Vertex{ /*pos*/{ -1.0f, 1.0f }, /*col*/{ 1, 1, 1 }, /*uv*/{ 0.00f, 0.00f } } };
	verts[1] = { Vertex{ /*pos*/{ 1.0f, 1.0f }, /*col*/{ 1, 1, 1 }, /*uv*/{ 0.17f, 0.00f } } };
	verts[2] = { Vertex{ /*pos*/{ 1.0f, -1.0f }, /*col*/{ 1, 1, 1 }, /*uv*/{ 0.17f, 0.25f } } };
	verts[3] = { Vertex{ /*pos*/{ -1.0f, -1.0f }, /*col*/{ 1, 1, 1 }, /*uv*/{ 0.00f, 0.25f } } };

	glBindVertexArray(this->VAO);

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);


	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3 * 2, NULL, GL_DYNAMIC_DRAW);


	activeShaderProgram = createProgram("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");


	GLint posAttrib = activeShaderProgram.getAttributeLocation("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(
		posAttrib,		//location
		2,				//size -> components attribute consists of
		GL_FLOAT,		//underlying type
		GL_FALSE,		//normalized
		sizeof(Vertex), //stride -> start reading next attribute after skipping 'sizeof(Vertex)' bytes
		0				//attibute offset -> this is the first attribute, no offset needed
	);

	GLint colAttrib = activeShaderProgram.getAttributeLocation("color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(
		colAttrib,							//location
		3, 									//size -> components attribute consists of
		GL_FLOAT,							//underlying type
		GL_FALSE,							//normalized
		sizeof(Vertex),						//stride -> start reading next attribute after skipping 'sizeof(Vertex)' bytes
		(const GLvoid*) sizeof(glm::vec2)	//attibute offset -> skip sizeof( previous attribute(-s) ) bytes forward
	);

	GLint texCoordAttrib = activeShaderProgram.getAttributeLocation("texcoord");
	glEnableVertexAttribArray(texCoordAttrib);
	glVertexAttribPointer(
		texCoordAttrib,											//location
		2, 														//size -> components attribute consists of
		GL_FLOAT, 												//underlying type
		GL_FALSE, 												//normalized
		sizeof(Vertex), 										//stride -> start reading next attribute after skipping 'sizeof(Vertex)' bytes
		(const GLvoid*)(sizeof(glm::vec2) + sizeof(glm::vec3))	//attibute offset -> skip sizeof( previous attribute(-s) ) bytes forward
	);

	glUniform1i(activeShaderProgram.getUniformLocation("texOne"), 0);

	glClearDepth(1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


}



void SpriteRenderer::DrawSprite(Texture &texture, glm::vec2 position,
	glm::vec2 size, GLfloat rotate, glm::vec3 color)
{

	GLint modelID, viewID, projectionID;;

	modelID = activeShaderProgram.getUniformLocation("model");
	viewID = activeShaderProgram.getUniformLocation("view");
	projectionID = activeShaderProgram.getUniformLocation("projection");

	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 proj = glm::perspective(PI / 1.78f, (GLfloat)1024 / (GLfloat)760, 0.1f, -10.0f);

	glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(proj));

	glm::mat4 modelMatrix(1.f);
	//Just have to add transformation
	glm::mat4 translate = glm::translate(modelMatrix, glm::vec3(position, 0.f));
	glm::mat4 rotateM = glm::rotate(modelMatrix, rotate, glm::vec3(0,0,1));
	glm::mat4 scale = glm::scale(modelMatrix, glm::vec3(size, 0.f));

	glm::mat4 model = translate * rotateM * scale;

	glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
	
	/*
	Have frames from Animationcontroller inserted (currently including the controller in main breaks it)
	change verts uv to frame[1], frame[2] and so on

	verts[1].uv = frame[1];
	verts[2].uv = frame[2];
	verts[3].uv = frame[3];
	verts[4].uv = frame[4];

	*/

	

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