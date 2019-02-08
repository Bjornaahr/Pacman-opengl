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
#include "textureManager.h"
#include "spriterenderer.h"

ShaderProgram activeShaderProgram;
SpriteRenderer  *Renderer;

struct Vertex {
	glm::vec2 position;
	glm::vec3 color;
	glm::vec2 uv;
};

void static_code(GLuint &vao, GLuint &vbo, GLuint &ebo, GLuint(&textures)[2]) {

	//Creates a spriterenderer
	Renderer = new SpriteRenderer();

	//All of this will be moved later
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
	//Loads texture (Path, name for future refrence)
	TextureManager::LoadTexture("resources/assets/pacman.png", "packman");


	glActiveTexture(GL_TEXTURE0);

	/*//Sample code for loading additional sprite. But not used in this code
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

}


void dynamic_code()
{
	// Use a Vertex Array Object
	
	//Draws packman, (Texture, position, size, rotation, color)
	Renderer->DrawSprite(TextureManager::GetTexture("packman"),
		glm::vec2(0, 0), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

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
	
		dynamic_code();

		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
