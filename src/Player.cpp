
#include "player.h"
#include <iostream>
#include <GFX/gfx.h>
#define PI (float)3.14159265359

Player::Player() {
	this->x = 2.5;
	this->y = 2;
	this->Size = glm::vec2(0.09f, 0.09f);
	direction = glm::vec2(0.f, 0.f);
	speed = 1.f;
}

void Player::movement(GLFWwindow *w, bool coll, double deltatime) {
	float t = 0.1f;
	float rotate;
	// Move forward
	
	Position.x = x;
	Position.y = y;
		if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
			direction.x = 0.f;
			direction.y = 1.f;
			this->rotate = PI;
			speed = 1.f;
			x = floor(x / t) * t + t / 2;
		}
		// Move backward
		if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
			direction.x = 0.f;
			direction.y = -1.f;
			this->rotate = 0;
			speed = 1.f;
			x = floor(x / t) * t + t / 2;
		}
		// Strafe right
		if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
			direction.x = 1.f;
			direction.y = 0.f;
			this->rotate = PI / 2;
			speed = 1.f;
			y = floor(y / t) * t + t / 2;
		}
		// Strafe left
		if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
			direction.x = -1.f;
			direction.y = 0.f;
			this->rotate = (3 * PI) / 2;
			speed = 1.f;
			y = floor(y / t) * t + t / 2;
		}
		// Should work as collision detection
		// needs some more changes to make it work
		// namely have tiledata be correct
		
		if (direction.y == 1) {
			int x1 = floor(x / t);
			int y1 = floor(y / t);
			if (tileData[x1][y1 + 1] == 0) {
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else {
				direction.y = 0.0f;
				y = floor(y / t) * t + t / 2;
			}
		}
		if (direction.y == -1) {
			int x1 = floor(x / t);
			int y1 = floor(y / t);
			if (tileData[x1][y1 - 1] == 0) {
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else {
				direction.y = 0.0f;
				y = floor(y / t) * t + t / 2;
			}
		}
		if (direction.x == 1) {
			int x1 = floor(x / t);
			int y1 = floor(y / t);
			if (tileData[x1 + 1][y1] == 0) {
				direction.x = 1.0f;
				direction.y = .0f;
			}
			else {
				direction.x = 0.0f;
				x = floor(x / t) * t + t / 2;
			}
		}
		if (direction.x == -1) {
			int x1 = floor(x / t);
			int y1 = floor(y / t);
			if (tileData[x1 - 1][y1] == 0) {
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
			else {
				direction.x = 0.0f;
				x = floor(x / t) * t + t / 2;
			}
		}
		

	
	
}

float Player::rotation() {
	return this->rotate;
}

void Player::addTileToPlayer(std::vector<std::vector<GLuint>> tile)
{
	tileData = tile;
	GFX_INFO("tiledata: ", tileData[0][0]);
}

glm::vec2 Player::translate(double deltaTime) {
	this->x += direction.x * deltaTime * speed;
	this->y += direction.y * deltaTime * speed;
	return glm::vec2(this->x, this->y);
}


