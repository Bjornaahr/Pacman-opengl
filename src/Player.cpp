#include "player.h"
#include <GLFW/glfw3.h>

Player::Player() {

}

void Player::Movement() {
	// Move forward
	if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}
}
