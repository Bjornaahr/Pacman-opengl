#include "player.h"
#include <iostream>
#define PI (float)3.14159265359

Player::Player() {
	this->x = 2.5;
	this->y = 2;
	this->Size = glm::vec2(0.1f, 0.1f);

	direction = glm::vec2(0.f, 0.f);
	speed = 1.f;
}

void Player::movement(GLFWwindow *w, bool coll, double deltatime) {
	
	float rotate;
	// Move forward
	
	Position.x = x;
	Position.y = y;
	if(coll) {

	if (direction.x == -1.f) {
		this->x += -direction.x * 0.01f;
	}
	else if (direction.x == 1.f) {
		this->x -= direction.x * 0.01f;
	}
	else if (direction.y == -1.f) {
		this->y += -direction.y * 0.01f;
	}
	else if (direction.y == 1.f) {
		this->y += -direction.y * 0.01f;
	}

	speed = 0.f;

	}
	else {
		if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
			direction.x = 0.f;
			direction.y = 1.f;
			this->rotate = PI;
			speed = 1.f;
		}
		// Move backward
		if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
			direction.x = 0.f;
			direction.y = -1.f;
			this->rotate = 0;
			speed = 1.f;
		}
		// Strafe right
		if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
			direction.x = 1.f;
			direction.y = 0.f;
			this->rotate = PI / 2;
			speed = 1.f;
		}
		// Strafe left
		if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
			direction.x = -1.f;
			direction.y = 0.f;
			this->rotate = (3 * PI) / 2;
			speed = 1.f;
		}

	}
	
}

float Player::rotation() {
	return this->rotate;
}

glm::vec2 Player::translate(double deltaTime) {
	this->x += direction.x * deltaTime * speed;
	this->y += direction.y * deltaTime * speed;
	return glm::vec2(this->x, this->y);
}


