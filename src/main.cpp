#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <imgui.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
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

bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.4f, 0.55f, 0.60f, 1.00f);


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
	MapLoader two;
	two.Load("resources/levels/level1", WIDTH, HEIGHT, player, ghosts);

	//Add level to level vector
	Levels.push_back(one);
	Levels.push_back(two);
	//Sets level to 0 getting ready to load the correct level
	Level = 1;
}


void dynamic_code(GLFWwindow *w, double deltaTime, bool *exit)
{
	// Use a Vertex Array Object
	glClearColor(0.15f, 0.15f, 0.15f, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static bool menu = true;
	static bool wasPressed = false;

	// enters main menu if you die showing score
	static bool dead = false;

	static bool comp = false;

	// Score for game
	static int score = 0;
	if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		wasPressed = true;
	}
	if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
		if (wasPressed) {
			menu = !menu;
		}
		wasPressed = false;
	}
	static bool start = true;
	if (menu) {
		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{



			ImGui::Begin("Menu");
			if (dead) {
				if (ImGui::Button("Restart")) {
					menu = false;
					dead = false;
					Score = 0;
				}

			}
			else if (start) {
				if (ImGui::Button("Start")) {
					dead = false;
					menu = false;
					start = false;
				}
			}
			else {
				if (ImGui::Button("Resume"))	menu = false;


				if (ImGui::Button("Restart")) {
					Lives = 3;
					PelletsDestoyed = 0;
					player->Reset();
					Levels[Level].Reset();
					dead = false;
					menu = false;
					GFX_INFO("Score: %i\n PelletsDestoryed: %i", Score, PelletsDestoyed);
				}

			}



			if (ImGui::Button("Exit"))		*exit = true;

			ImGui::Text("Score %d", Score);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
	}
	else {
		//Moves the player also checks for colision against wall
		player->movement(w, Level);
		for (int i = 0; i < 4; i++) ghosts[i]->movement(w, Level);
		ImGui::Begin("Score");
		ImGui::Text("Score %d", Score);
		ImGui::Text("Lives %d", Lives);
		ImGui::End();

		//Checks for collision against pellets and ghosts
		Collisions();

		//Draws level
		Levels[Level].Draw(*Renderer);

		//Draws packman, (Texture, position, size, rotation, color, shift in UV(for animations))
		Renderer->DrawSprite(TextureManager::GetTexture("pacman"),
			player->translate(deltaTime), glm::vec2(.5f, .5f), player->rotation(), glm::vec3(1.0f, 1.0f, 1.0f), player->animation(deltaTime));
		for (int i = 0; i < 4; i++) {
			Renderer->DrawSprite(TextureManager::GetTexture("pacman"),
				ghosts[i]->translate(deltaTime), glm::vec2(.5f, .5f), 0, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.8333335, 0));
		}
		if (dead) {
			menu = true;
			///Restart function?
			Lives = 3;
			PelletsDestoyed = 0;
			player->Reset();
			Levels[Level].Reset();
			GFX_INFO("Score: %i\n PelletsDestoryed: %i", Score, PelletsDestoyed);
		}
	}




	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//Check if amount of pellets destoyed is enough to complete level
	if (Levels[Level].Pelletamount == PelletsDestoyed) {
		//Set level to completed
		comp = Levels[Level].IsCompleted();
	}

	if (Lives <= 0) {
		dead = true;
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
	const char* glsl_version = "#version 330";
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
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init(glsl_version);
	io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;
	static_code();
	glClearColor(1,1,1,1);
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	double deltaTime = 0;
	double oldTime = 0;
	bool exit = false;
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
		dynamic_code(window, deltaTime, &exit);

		glfwSwapBuffers(window);
		glfwPollEvents();
		oldTime = currentTime;
	} 
	while (!exit &&
		glfwWindowShouldClose(window) == 0);
	glfwDestroyWindow(window);
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
