#include "maploader.h"
#include "textureManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <GFX/gfx.h>



void MapLoader::Load(const GLchar *file, GLuint width, GLuint height, Player *p, Ghost *ghost[]) {

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
			p->addTileToPlayer(tileData);
		for (int i = 0; i < 4; i++) {
			ghost[i]->addTileToGhost(tileData);
		}

			Pelletamount = 0;
			this->init(tileData, width, height, p);
	}
}

void MapLoader::init(std::vector<std::vector<GLuint>> tileData, GLuint lvlwidth, GLuint lvlheight, Player *p) {
	GLuint height = tileData.size();
	GLuint width = tileData[0].size();
	GLfloat unit_width = lvlwidth / static_cast<GLfloat>(width);
	GLfloat unit_height = lvlheight / height;

	std::cout << unit_width << std::endl << unit_height << std::endl;

	for (GLfloat y = 0; y < height; y++) {
		for (GLfloat x = 0; x < width; x++) {

			if (tileData[y][x] == 1) {
				glm::vec2 pos(x, y);
				glm::vec2 size(0.6f, 0.6f);
				GameObject wall(pos, size, TextureManager::GetTexture("wall"));
				this->Bricks.push_back(wall);
			}

			if (tileData[y][x] == 0) {
				glm::vec2 pos(x, y);
				glm::vec2 size(0.1f, 0.1f);
				GameObject pellet(pos, size, TextureManager::GetTexture("pellet"));
				this->Pellets.push_back(pellet);
				++Pelletamount;
			}

			if (tileData[y][x] == 2) {
				p->getspawn(x, y);
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
	GFX_INFO("Level completed!");
	return 0;
}