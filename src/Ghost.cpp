#include "Ghost.h"

Ghost::Ghost() {
	this->x = 2.0f;
	this->y = 4.0f;
	this->Size = glm::vec2(0.09f, 0.09f);
	direction = glm::vec2(0.f, 0.f);
	speed = 3.5f;

}


void Ghost::movement(GLFWwindow *w, int level){
	delta++;
	float t = 1.f;
	float rotate;
	// Move forward
	float divisor = 128;
	Position.x = x;
	Position.y = y;
	currentLevel = level;

	if (fmod(delta, 50) == 0) {
		int random = rand() % 4;
		if (random == 0 && tileData[currentLevel][y + 1.0f][x] == 0) {
			direction.x = 0.f;
			direction.y = 1.f;
			x = floor(x / t) * t + t / divisor;
		}
		// Move backward
		if (random == 1 && tileData[currentLevel][y - 1.0f][x] == 0) {
			direction.x = 0.f;
			direction.y = -1.f;
			x = floor(x / t) * t + t / divisor;
		}
		// Strafe right
		if (random == 2 && tileData[currentLevel][y][x + 1.0f] == 0) {
			direction.x = 1.f;
			direction.y = 0.f;
			y = floor(y / t) * t + t / divisor;
		}
		// Strafe left
		if (random == 3 && tileData[currentLevel][y][x + 1.0f] == 0) {
			direction.x = -1.f;
			direction.y = 0.f;
			y = floor(y / t) * t + t / divisor;
		}
	}

			//If ghost is going up
			if (direction.y == 1) {
				int x1 = floor(x / t);
				int y1 = floor(y / t);
				//Check if tile in front is walkable
				if (tileData[currentLevel][y1 + 1][x1] == 0 || tileData[currentLevel][y1 + 1.0f][x1] == 2) {
					direction.x = 0.0f;
					direction.y = 1.0f;
				}
				//If not walkable stop ghost and center on tile
				else {
					direction.y = 0.0f;
					y = floor(y / t) * t + t / divisor;
				}
			}

			//If ghost is going down
			if (direction.y == -1) {
				int x1 = floor(x / t);
				int y1 = floor(y / t);
				//Check if tile in front is walkable
				if (tileData[currentLevel][y1 - 1][x1] == 0 || tileData[currentLevel][y1 - 1.0f][x1] == 2) {
					direction.x = 0.0f;
					direction.y = -1.0f;
				}
				else {
					//If not walkable stop ghost and center on tile
					direction.y = 0.0f;
					y = floor(y / t) * t + t / divisor;
				}
			}

			//If ghost is going right
			if (direction.x == 1) {
				int x1 = floor(x / t);
				int y1 = floor(y / t);
				//Check if tile in front is walkable
				if (tileData[currentLevel][y1][x1 + 1] == 0 || tileData[currentLevel][y1][x1 + 1.0f] == 2) {
					direction.x = 1.0f;
					direction.y = .0f;
				}
				else {
					//If not walkable stop ghost and center on tile
					direction.x = 0.0f;
					x = floor(x / t) * t + t / divisor;
				}
			}

			//If ghost is going left
			if (direction.x == -1) {
				int x1 = floor(x / t);
				int y1 = floor(y / t);
				//Check if tile in front is walkable
				if (tileData[currentLevel][y1][x1 - 1] == 0 || tileData[currentLevel][y1][x1 - 1.0f] == 2) {
					direction.x = -1.0f;
					direction.y = 0.0f;
				}
				else {
					//If not walkable stop ghost and center on tile
					direction.x = 0.0f;
					x = floor(x / t) * t + t / divisor;
				}
			}



}

void Ghost::addTileToGhost(std::vector<std::vector<GLuint>> tile)
{
	tileData.push_back(tile);
}

glm::vec2 Ghost::translate(double deltaTime) {
	this->x += direction.x * deltaTime * speed;
	this->y += direction.y * deltaTime * speed;
	return glm::vec2(this->x, this->y);
}