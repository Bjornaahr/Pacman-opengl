/*#include "maploader.h"
#include <fstream>
#include <sstream>
#include <vector>

void MapLoader(const GLchar *file, GLuint width, GLuint height) {
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

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint lvlwidth, GLuint lvlheight) {
	GLuint height = tileData.size();
	GLuint width = tileData[0].size();
	GLfloat unit_width = lvlwidth / static_cast<GLfloat>(width);
	GLfloat unit_height = lvlHeight / height;

	for (GLuint y = 0; y < height; ++y) {
		for (GLuint x = 0; x < width; ++x) {
			if(tileData[y][x] == 1){//Wall
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit:height);
				GameObject obj(pos, size, );
		}
	}
}*/