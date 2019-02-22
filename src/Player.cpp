
#include "player.h"
#include <iostream>
#include <GFX/gfx.h>
#define PI (float)3.14159265359

Player::Player() {
	this->x = 2.0f;
	this->y = 4.0f;
	this->Size = glm::vec2(0.09f, 0.09f);
	direction = glm::vec2(0.f, 0.f);
	speed = 1.f;

	//Numbers representing UV coordinates for spritesheet animation
	animationFrames[0] = glm::vec2(0, 0);
	animationFrames[1] = glm::vec2(0.16f, 0);
	animationFrames[2] = glm::vec2(0.32f, 0);
	animationFrames[3] = glm::vec2(0.48f, 0);
	currentFrame = 0;


}


// Source for how we decided to do collision / cenetring
// https://www.dropbox.com/s/pbcokfxxdwsvcr7/Pacman.rar?file_subpath=%2FPacman%2FAIE+Basic+Framework2
//
void Player::movement(GLFWwindow *w, double deltatime) {
	float t = 1.f;
	float rotate;
	// Move forward
	float divisor = 128;
	Position.x = x;
	Position.y = y;

			if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
				direction.x = 0.f;
				direction.y = 1.f;
				this->rotate = PI;
				speed = 5.f;
				x = floor(x / t) * t + t / divisor;
			}
			// Move backward
			if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
				direction.x = 0.f;
				direction.y = -1.f;
				this->rotate = 0;
				speed = 5.f;
				x = floor(x / t) * t + t / divisor;
			}
			// Strafe right
			if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
				direction.x = 1.f;
				direction.y = 0.f;
				this->rotate = PI / 2;
				speed = 5.f;
				y = floor(y / t) * t + t / divisor;
			}
			// Strafe left
			if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
				direction.x = -1.f;
				direction.y = 0.f;
				this->rotate = (3 * PI) / 2;
				speed = 5.f;
				y = floor(y / t) * t + t / divisor;
			}
		

		// Should work as collision detection
		// needs some more changes to make it work
		// namely have tiledata be correct
		
		if (direction.y == 1) {
			int x1 = floor(x / t);
			int y1 = floor(y / t);
			if (tileData[y1 + 1][x1] == 0) {
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else {
				direction.y = 0.0f;
				y = floor(y / t) * t + t / divisor;
			}
		}
		if (direction.y == -1) {
			int x1 = floor(x / t);
			int y1 = floor(y / t);
			if (tileData[y1 - 1][x1] == 0) {
				direction.x = 0.0f;
				direction.y = -1.0f;
			}
			else {
				direction.y = 0.0f;
				y = floor(y / t) * t + t / divisor;
			}
		}
		if (direction.x == 1) {
			int x1 = floor(x / t);
			int y1 = floor(y / t);
			if (tileData[y1][x1 + 1] == 0) {
				direction.x = 1.0f;
				direction.y = .0f;
			}
			else {
				direction.x = 0.0f;
				x = floor(x / t) * t + t / divisor;
			}
		}
		if (direction.x == -1) {
			int x1 = floor(x / t);
			int y1 = floor(y / t);
			if (tileData[y1][x1 - 1] == 0) {
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
			else {
				direction.x = 0.0f;
				x = floor(x / t) * t + t / divisor;
			}
		}
}

float Player::rotation() {
	return this->rotate;
}

void Player::addTileToPlayer(std::vector<std::vector<GLuint>> tile)
{
	tileData = tile;
}

glm::vec2 Player::translate(double deltaTime) {
	this->x += direction.x * deltaTime * speed;
	this->y += direction.y * deltaTime * speed;
	return glm::vec2(this->x, this->y);
}


//Deals with player animation
glm::vec2 Player::animation(double deltaTime) {
	//Counts up on delta
	delta++;
	//Check if on last frame
	if (currentFrame == 3) {
		forward = false;
	}
	//Check if on first frame
	else if (currentFrame == 0) {
		forward = true;
	}
	//check if delta modolu speed is 0
	if (fmod(delta, 2) == 0) {
		//Resets delta
		delta = 0;
		//Check if to play animation forward or backwards
		if (forward == true) {
			//Returns currentframe and increment to next frame
			return animationFrames[currentFrame++];
		} else return animationFrames[currentFrame--];
	}
	else {
		//Returns currentframe until time
		return animationFrames[currentFrame];
	}

}


void Player::getspawn(float xSpawn, float ySpawn) {
	this->x = xSpawn;
	this->y = ySpawn;
}




