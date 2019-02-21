#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "gameobject.h"


class Player : public GameObject{
private:
	glm::vec2 direction;
	float x, y;
	float rotate;
	float speed;
	std::vector<std::vector<GLuint>> tileData;
	//Frames in animation UV
	glm::vec2 animationFrames[4];
	//Current frame to display
	int currentFrame;
	//Number to check when we can change animation frame
	double delta;
	//Bool to check if we play animation backwards or forwards
	bool forward;

public:
	/// As player and ghost is using the same class. make seperate constructors for both
	Player();
	~Player();
	void movement(GLFWwindow *w, bool player, double deltatime);

	float rotation();
	void addTileToPlayer(std::vector<std::vector<GLuint>> tile);
	glm::vec2 translate(double deltaTime);
	glm::vec2 animation(double deltaTime);

};