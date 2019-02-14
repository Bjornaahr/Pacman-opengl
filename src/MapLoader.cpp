#include "maploader.h"
#include "textureManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void MapLoader::Load(const GLchar *file, GLuint width, GLuint height) {
	//Deletes old map
	this->Bricks.clear();
	//Load from file
	GLuint tileCode;
	MapLoader level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream) {
		while (std::getline(fstream, line)) {
			std::istringstream  sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) {
				row.push_back(tileCode);
				tileData.push_back(row);
			}
			if (tileData.size() > 0) {
				this->init(tileData, width, height);
			}
		}
	}
}

void MapLoader::init(std::vector<std::vector<GLuint>> tileData, GLuint lvlwidth, GLuint lvlheight) {
	GLuint height = tileData.size();
	GLuint width = tileData[0].size();
	GLfloat unit_width = lvlwidth / static_cast<GLfloat>(width);
	GLfloat unit_height = lvlheight / height;

	for (GLuint y = 0; y < height; ++y) {
		for (GLuint x = 0; x < width; ++x) {
			if (tileData[y][x] == 1) {//Wall
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				GameObject obj(pos, size, TextureManager::GetTexture("wall"), glm::vec3(0.8f, 0.8f, 0.7f));
				this->Bricks.push_back(obj);
			}
		}
	}
}

void MapLoader::Draw(SpriteRenderer &renderer) {
	for (GameObject &tile : this->Bricks) {
		tile.Draw(renderer);
	}
}

GLboolean MapLoader::IsCompleted()
{
	return 0;
}