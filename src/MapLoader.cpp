#include "maploader.h"
#include "textureManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void MapLoader::Load(const GLchar *file, GLuint width, GLuint height) {

	this->Bricks.clear();
	this->Pellets.clear();

	GLuint tileCode;
	MapLoader level;
	std::string line;
	std::ifstream in(file);
	std::vector<std::vector<GLuint>> tileData;

	if (in) {
		while (std::getline(in, line)) {
			std::istringstream sstream(line);
			std::vector<GLuint> row;

			while (sstream >> tileCode)
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData, width, height);
	}
}

void MapLoader::init(std::vector<std::vector<GLuint>> tileData, GLuint lvlwidth, GLuint lvlheight) {
	GLuint height = tileData.size();
	GLuint width = tileData[0].size();
	GLfloat unit_width = lvlwidth / static_cast<GLfloat>(width);
	GLfloat unit_height = lvlheight / height;

	std::cout << unit_width << std::endl << unit_height << std::endl;

	for (GLfloat y = 0; y < height; y++) {
		for (GLfloat x = 0; x < width; x++) {
			if (tileData[y][x] == 1) {
				glm::vec2 pos((x / 6) - 2.3, (y / 6) - 3.0f);
				glm::vec2 size(0.1f, 0.1f);
				GameObject wall(pos, size, TextureManager::GetTexture("wall"), glm::vec3(0.f, 0.f, 0.f));
				this->Bricks.push_back(wall);
			}

			if (tileData[y][x] == 0) {
				glm::vec2 pos((x / 6) - 2.3, (y / 6) - 3.0f);
				glm::vec2 size(0.01f, 0.01f);
				GameObject pellet(pos, size, TextureManager::GetTexture("pellet"), glm::vec3(0.f, 0.f, 0.f));
				this->Pellets.push_back(pellet);
			}

		}
	}

}

void MapLoader::Draw(SpriteRenderer &renderer) {
	for (GameObject &tile : this->Bricks) {
		tile.Draw(renderer);
	}

	for (GameObject &pellet : this->Pellets) {
		if (!pellet.isDestoroyed) {
			pellet.Draw(renderer);
		}
	}
}

GLboolean MapLoader::IsCompleted()
{
	return 0;
}