#include "player.h"
#define PI (float)3.14159265359

Player::Player() {
	direction = glm::vec2(0.f, 0.f);
	this->x = 0;
	this->y = 0;
}

glm::vec2 Player::movement(GLFWwindow *w, double deltaTime) {
	
	float rotate;
	// Move forward
	
	if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
		direction.x = 0.f;
		direction.y = 1.f;
		this->rotate = PI;
	}
	// Move backward
	if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
		direction.x = 0.f;
		direction.y = -1.f;
		this->rotate = 0;
	}
	// Strafe right
	if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
		direction.x = 1.f;
		direction.y = 0.f;
		this->rotate = PI / 2;
	}
	// Strafe left
	if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
		direction.x = -1.f;
		direction.y = 0.f;
		this->rotate = (3 * PI) / 2;
		}
	
	this->x += direction.x * deltaTime * 1.f;
	this->y += direction.y * deltaTime * 1.f;
	return glm::vec2(this->x, this->y);
}

float Player::rotation() {
	return this->rotate;
}


