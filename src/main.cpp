#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <imgui.h>
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
#include "Ghost.h"
#include "gameobject.h"
#include "maploader.h"

//We borrowed a lot of code and examples from
//https://learnopengl.com/
//

SpriteRenderer  *Renderer;
Player *player;
Ghost *ghosts[4];

std::vector<MapLoader> Levels;
GLuint Level;

int WIDTH = 1024, HEIGHT = 768;
int Score;
int PelletsDestoyed;
int Lives = 3;

GLboolean CheckCollision(GameObject &one, GameObject &two);
GLboolean Collision(GLFWwindow *w, bool coll, double deltatime);
void Collisions();


struct Vertex {
	glm::vec2 position;
	glm::vec3 color;
	glm::vec2 uv;
};

void static_code() {

	//Creates a spriterenderer
	Renderer = new SpriteRenderer();
	player = new Player();


	for (int i = 0; i < 4; i++) ghosts[i] = new Ghost();
	

	//Loads texture (Path, name for future refrence)
	TextureManager::LoadTexture("resources/assets/pacman.png", "pacman");
	TextureManager::LoadTexture("resources/assets/block.png", "wall");
	TextureManager::LoadTexture("resources/assets/pellet.png", "pellet");



	MapLoader one;
	//Loads map WIDTH and HEIGHT dosn't do anything
	one.Load("resources/levels/level0", WIDTH, HEIGHT, player, ghosts);
	//Add level to level vector
	Levels.push_back(one);
	//Sets level to 0 getting ready to load the correct level
	Level = 0;


}


void dynamic_code(GLFWwindow *w, double deltaTime)
{
	// Use a Vertex Array Object
	glClearColor(0.15f, 0.15f, 0.15f, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//Moves the player also checks for colision against wall
	player->movement(w, deltaTime);

	for (int i = 0; i < 4; i++) ghosts[i]->movement(w, deltaTime);


	//Draws level
	Levels[Level].Draw(*Renderer);

	//Draws packman, (Texture, position, size, rotation, color, shift in UV(for animations))
	Renderer->DrawSprite(TextureManager::GetTexture("pacman"),
		player->translate(deltaTime), glm::vec2(.5f, .5f), player->rotation(), glm::vec3(1.0f, 1.0f, 1.0f), player->animation(deltaTime));
	for (int i = 0; i < 4; i++) {
		Renderer->DrawSprite(TextureManager::GetTexture("pacman"),
			ghosts[i]->translate(deltaTime), glm::vec2(.5f, .5f), 0, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.8333335, 0));
	}

	//Checks for collision against pellets
	Collisions();
	//Check if amount of pellets destoyed is enough to complete level
	if (Levels[Level].Pelletamount == PelletsDestoyed) {
		//Set level to completed
		bool comp = Levels[Level].IsCompleted();
	}

}

//Check for collision between two GameObjects
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

//Checks for collision against pellets
void Collisions() {
	//Loops through all pellets in current level
	for (GameObject &pellet : Levels[Level].Pellets) {
		//Check for collision
		if (CheckCollision(*player, pellet) && !pellet.isDestoroyed) {
			//Destorys pellet
			pellet.isDestoroyed = true;
			//Increase score and pellets destoyed
			Score++;
			PelletsDestoyed++;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (CheckCollision(*ghosts[i], *player)) {
			GFX_INFO("Lost a life, Current lifes: %i", Lives);
			Lives--;
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
	
	// Set OpenGL options

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	static_code();
	glClearColor(1,1,1,1);
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	double deltaTime = 0;
	double oldTime = 0;
	/// Needs better animation/movement based on time so it is smooth at all times
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
		dynamic_code(window, deltaTime);

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
