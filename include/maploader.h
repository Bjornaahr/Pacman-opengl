#pragma once
#include "Player.h"
#include "gameobject.h"
#include "spriterenderer.h"
#include <vector>
#include "textureManager.h"
#include "Ghost.h"


class MapLoader
{
public:
	std::vector<GameObject> Bricks;
	std::vector<GameObject> Pellets;
	int Pelletamount;

	MapLoader() { }
	//Loads level from file
	void Load(const GLchar *file, GLuint width, GLuint height, Player *p, Ghost *ghost[]);

	void Draw(SpriteRenderer &renderer);

	GLboolean IsCompleted();
private:
	void init(std::vector<std::vector<GLuint>> tileData, GLuint lvlwidth, GLuint lvlheight, Player *p);

};