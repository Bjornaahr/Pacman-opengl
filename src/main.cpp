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
#include "textureManager.h"
#include "spriterenderer.h"
#include "player.h"
#include "gameobject.h"
#include "maploader.h"




SpriteRenderer  *Renderer;
Player *player;

std::vector<MapLoader> Levels;
GLuint Level;

int WIDTH = 1024, HEIGHT = 768;

GLboolean CheckCollision(GameObject &one, GameObject &two);
void Collision();

struct Vertex {
	glm::vec2 position;
	glm::vec3 color;
	glm::vec2 uv;
};

void static_code(GLuint &vao, GLuint &vbo, GLuint &ebo, GLuint(&textures)[2]) {

	//Creates a spriterenderer
	Renderer = new SpriteRenderer();
	player = new Player();

	//All of this will be moved later



	//Loads texture (Path, name for future refrence)
	TextureManager::LoadTexture("resources/assets/pacman.png", "packman");
	TextureManager::LoadTexture("resources/assets/block.png", "wall");


	MapLoader one; 
	one.Load("resources/levels/level0", WIDTH, HEIGHT);
	Levels.push_back(one);
	Level = 0;


}


void dynamic_code(GLFWwindow *w, glm::vec2 *p, double deltaTime)
{
	// Use a Vertex Array Object
	glClearColor(0.15f, 0.15f, 0.15f, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	*p = player->movement(w, deltaTime);
	//Draws packman, (Texture, position, size, rotation, color)
	Renderer->DrawSprite(TextureManager::GetTexture("packman"),
		*p, glm::vec2(0.2f, 0.2f), player->rotation(), glm::vec3(0.0f, 0.0f, 0.0f));

	Levels[Level].Draw(*Renderer);

	Collision();

}


GLboolean CheckCollision(GameObject &one, GameObject &two) {
	// Collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// Collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// Collision only if on both axes

	return collisionX && collisionY;
}

void Collision() {
	for (GameObject &box : Levels[Level].Bricks) {
		if (CheckCollision(*player, box)) {
			box.Rotation += 0.001;
			//Do stuff
		}

	}
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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Packman", NULL, NULL);
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
	double deltaTime = 0;
	double oldTime = 0;
	glm::vec2 p = glm::vec2(0.f, 0.f);
	
	do {
		
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last print was more than 1sec ago
											 // print and reset
			GFX_INFO("%f ms/frame", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;


			/*
			add animation steps?
			*/

		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		deltaTime = currentTime - oldTime;
		dynamic_code(window, &p, deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
		oldTime = currentTime;
	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
