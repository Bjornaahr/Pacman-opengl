/*#pragma once
#include "gameobject.h"

class MapLoader
{
	public
		std::vector<GameObject> Bricks;

	MapLoader() { }
	//Loads level from file
	void Load(const GLchar *file, GLuint width, GLuint height);

	void Draw();

	GLboolean IsCompleted();
private:
	void init(std::vector<std::vector<GLuint>> tileData, GLuint lvlwidth, GLuint lvlheight);

};*/