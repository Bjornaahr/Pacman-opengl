#include "player.h"
#define PI (float)3.14159265359

Player::Player() {
	this->x = 0;
	this->y = 0;
}

glm::vec2 Player::movement(GLFWwindow *w, double deltaTime) {
	
	float rotate;
	// Move forward
	
	if (direction[0]) this->y += 1.f * deltaTime * 1.f;
	if (direction[1]) this->y -= 1.f * deltaTime * 1.f;
	if (direction[2]) this->x += 1.f * deltaTime * 1.f;
	if (direction[3]) this->x -= 1.f * deltaTime * 1.f;
	
	
	if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
		this->y += 1.f * deltaTime * 1.f;
		this->rotate = PI;
		direction[0] = true;
		direction[1] = false;
		direction[2] = false;
		direction[3] = false;
			
	}
	// Move backward
	if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
		this->y -= 1.f * deltaTime * 1.f;
		this->rotate = 0;
		direction[0] = false;
		direction[1] = true;
		direction[2] = false;
		direction[3] = false;
	}
	// Strafe right
	if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
		this->x += 1.f * deltaTime * 1.f;
		this->rotate = PI / 2;
		direction[0] = false;
		direction[1] = false;
		direction[2] = true;
		direction[3] = false;
	}
	// Strafe left
	if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
		this->x -= 1.f * deltaTime * 1.f;
		this->rotate = (3 * PI) / 2;
		direction[0] = false;
		direction[1] = false;
		direction[2] = false;
		direction[3] = true;
		}
	

	return glm::vec2(this->x, this->y);
}

float Player::rotation() {
	return this->rotate;
}


