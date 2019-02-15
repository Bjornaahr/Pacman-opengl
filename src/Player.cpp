#include "player.h"


Player::Player() {
	this->x = 0;
	this->y = 0;
}

glm::vec2 Player::movement(GLFWwindow *w) {
	

	// Move forward
	if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
		this->y += 1.f * 0.3 * 1.f;
	}
	// Move backward
	if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
		this->y -= 1.f * 0.3 * 1.f;
	}
	// Strafe right
	if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
		this->x += 1.f * 0.3 * 1.f;
	}
	// Strafe left
	if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
		this->x -= 1.f * 0.3 * 1.f;
	}

	return glm::vec2(this->x, this->y);
}


