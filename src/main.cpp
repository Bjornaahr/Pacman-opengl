#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL.h> 
//NOTE: if you don't want such a huge library for image/texture loading, 
//		you can look into stb_image.h @ https://github.com/nothings/stb
//		as it should be sufficient for this and probably your projects

#define GFX_IMPLEMENTATION
#include <GFX/gfx.h>
#include "shaderloader.h"

ShaderProgram activeShaderProgram;

struct Vertex {
	glm::vec2 position;
	glm::vec3 color;
	glm::vec2 uv;
};

void static_code(GLuint &vao, GLuint &vbo, GLuint &ebo, GLuint(&textures)[2]) {

	glBindVertexArray(vao);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	glGenBuffers(1, &vbo);

	activeShaderProgram = createProgram("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, NULL, GL_DYNAMIC_DRAW);
	

	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3 * 2, NULL, GL_DYNAMIC_DRAW);

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
		(const GLvoid*) (sizeof(glm::vec2) + sizeof(glm::vec3))	//attibute offset -> skip sizeof( previous attribute(-s) ) bytes forward
	);

	// Load textures
	glGenTextures(2, textures);

	int width, height;
	unsigned char* image;
	float x, y, widthT, heightT;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	image = SOIL_load_image("resources/textures/spritesheet.png", &width, &height, 0, SOIL_LOAD_AUTO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);


	glUniform1i(activeShaderProgram.getUniformLocation("texOne"), 0);

	// ST- are (in most cases) equivalent to UV coordinates
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE1);

	//Sample code for loading additional sprite. But not used in this code
	glBindTexture(GL_TEXTURE_2D, textures[1]);

	image = SOIL_load_image("resources/assets/pacman.png", &width, &height, 0, SOIL_LOAD_AUTO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(activeShaderProgram.getUniformLocation("texTwo"), 1);
	GFX_INFO(
		"\nThe warning you now should've gotten is expected in this case\n"
		"as we've written code for how to bind a second texture,\n" 
		"though because this texture is not part of the shader code\n"
		"it's not possible to change its value\n\n"
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}


void dynamic_code(GLuint &vao, GLuint &vbo, GLuint &ebo, GLuint(&textures)[2])
{
	// Use a Vertex Array Object
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);


	

	Vertex verts[] = {
		Vertex{ /*pos*/{ 0.5f, 1.0f }, /*col*/{ 1, 0, 0 }, /*uv*/{ 0.00f, 0.00f } },
		Vertex{ /*pos*/{ 1.0f, 1.0f }, /*col*/{ 0, 1, 0 }, /*uv*/{ 0.25f, 0.00f } },
		Vertex{ /*pos*/{ 1.0f, 0.5f }, /*col*/{ 0, 0, 1 }, /*uv*/{ 0.25f, 0.25f } },
		Vertex{ /*pos*/{ 0.5f, 0.5f }, /*col*/{ 1, 1, 1 }, /*uv*/{ 0.00f, 0.25f } },
	};


	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
	
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0

	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(elements), elements);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const GLvoid*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


int main(void)
{
	// Initialise GLFW
	if (!glfwInit()) {
		GFX_ERROR("Failed to initialize GLFW\n");
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Lab 04", NULL, NULL);
	if (window == NULL) {
		GFX_ERROR("Failed to open GLFW window.\n");
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		GFX_ERROR("Failed to initialize GLEW\n");
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSwapInterval(1);
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint textures[2];
	
	// Set OpenGL options

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	static_code(vao,vbo, ebo, textures);
	glClearColor(1,1,1,1);
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	do {
	
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last print was more than 1sec ago
											 // print and reset
			GFX_INFO("%f ms/frame", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		dynamic_code(vao, vbo, ebo, textures);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
