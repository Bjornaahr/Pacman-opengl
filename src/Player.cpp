#include "player.h"


Player::Player() {

}

void Player::movement(GLFWwindow *w) {
	

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
}

float Player::xPosition()
{
	return this->x;
}

float Player::yPosition()
{
	return this->y;
}

