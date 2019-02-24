#include "maploader.h"
#include "textureManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <GFX/gfx.h>


//Loads map from file
void MapLoader::Load(const GLchar *file, GLuint width, GLuint height, Player *p, Ghost *ghost[]) {
	//Clears old data
	this->Bricks.clear();
	this->Pellets.clear();
	GLuint tileCode;
	MapLoader map;
	std::string line;
	std::ifstream in(file);
	//To store the tiledata
	std::vector<std::vector<GLuint>> tileData;
	//If there is a file
	if (in) {
		//Reasd each line from the file
		while (std::getline(in, line)) {
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			//Separates numbers with spaces
			while (sstream >> tileCode)
				//Add a row to row vector
				row.push_back(tileCode);
			//Add row to mapvector
			tileData.push_back(row);
		}
		//If there is data in vector
		if (tileData.size() > 0) {
			//Send map to player
			p->addTileToPlayer(tileData);
			//Send map to  ghost
			for (int i = 0; i < 4; i++) {
				ghost[i]->addTileToGhost(tileData);
			}
			//Reset pelletamount
			Pelletamount = 0;
			this->init(tileData, width, height, p);
		}
		else {
			GFX_WARN("NO TILEDATA");
		}
		
	}
	else {
		GFX_WARN("No file");
	}
	in.close();

}
//Initilalize map
void MapLoader::init(std::vector<std::vector<GLuint>> tileData, GLuint lvlwidth, GLuint lvlheight, Player *p) {
	GLuint height = tileData.size();
	GLuint width = tileData[0].size();
	//Loops through each column
	for (GLfloat y = 0; y < height; y++) {
		//Loops through each row
		for (GLfloat x = 0; x < width; x++) {
			//Create a wall if number is 1
			if (tileData[y][x] == 1) {
				glm::vec2 pos(x, y);
				glm::vec2 size(0.5f, 0.5f);
				GameObject wall(pos, size, TextureManager::GetTexture("wall"));
				this->Bricks.push_back(wall);
			}
			//Create a pellet if number is 0
			if (tileData[y][x] == 0) {
				glm::vec2 pos(x, y);
				glm::vec2 size(0.1f, 0.1f);
				GameObject pellet(pos, size, TextureManager::GetTexture("pellet"));
				this->Pellets.push_back(pellet);
				++Pelletamount;
			}
			//Send spawn to player if number is 2
			if (tileData[y][x] == 2) {
				GFX_INFO("SpawnPoint");
				p->getspawn(x, y);
			}

		}
	}
	GFX_INFO("Loading level done");
}
//Render map
void MapLoader::Draw(SpriteRenderer &renderer) {
	//Loops though and render walls
	for (GameObject &tile : this->Bricks) {
		tile.Draw(renderer);
	}
	//Loops through and renders pellets
	for (GameObject &pellet : this->Pellets) {
		if (!pellet.isDestoroyed) {
			pellet.Draw(renderer);
		}
	}
}

//Reset map
void MapLoader::Reset() {
	//Loops through each pellet and set state to not destoryed
	for (GameObject &pellet : this->Pellets) {
		pellet.isDestoroyed = false;
	}
}

//Level completed
GLboolean MapLoader::IsCompleted()
{
	GFX_INFO("Level completed!");
	return 0;
}