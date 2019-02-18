#include "player.h"
#define PI (float)3.14159265359

Player::Player() {
	this->x = 0;
	this->y = 0;
}

glm::vec2 Player::movement(GLFWwindow *w, double deltaTime) {
	
	float rotate;
	// Move forward
	if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
		this->y += 1.f * deltaTime * 1.f;
		this->rotate = PI;
	}
	// Move backward
	if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
		this->y -= 1.f * deltaTime * 1.f;
		this->rotate = 0;
	}
	// Strafe right
	if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
		this->x += 1.f * deltaTime * 1.f;
		this->rotate = PI / 2;
	}
	// Strafe left
	if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
		this->x -= 1.f * deltaTime * 1.f;
		this->rotate = (3* PI) / 2;
	}

	return glm::vec2(this->x, this->y);
}

float Player::rotation() {
	return this->rotate;
}


