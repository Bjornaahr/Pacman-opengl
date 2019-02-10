#include "player.h"


Player::Player() {

}

void Player::movement(GLFWwindow *w, glm::vec2 *position) {
	glm::vec2 speed = glm::vec2(1, 1);
	// Move forward
	glm::vec2 d = glm::vec2(0, 1);
	glm::vec2 r = glm::vec2(1, 0);
	if (glfwGetKey(w, GLFW_KEY_UP) == GLFW_PRESS) {
		position += d * speed;
	}
	// Move backward
	if (glfwGetKey(w, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= d * speed;
	}
	// Strafe right
	if (glfwGetKey(w, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += r * speed;
	}
	// Strafe left
	if (glfwGetKey(w, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= r * speed;
	}
}
