#pragma once
#include "gameobject.h"
#include "spriterenderer.h"
#include <vector>
#include "textureManager.h"


class MapLoader
{
public:
	std::vector<GameObject> Bricks;
	std::vector<GameObject> Pellets;


	MapLoader() { }
	//Loads level from file
	void Load(const GLchar *file, GLuint width, GLuint height);

	void Draw(SpriteRenderer &renderer);

	GLboolean IsCompleted();
private:
	void init(std::vector<std::vector<GLuint>> tileData, GLuint lvlwidth, GLuint lvlheight);

};