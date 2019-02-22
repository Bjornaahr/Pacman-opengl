#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "gameobject.h"


class Ghost : public GameObject {
private:
	glm::vec2 direction;
	float x, y;
	float speed;
	std::vector<std::vector<GLuint>> tileData;
	int delta;

public:
	/// As player and ghost is using the same class. make seperate constructors for both
	Ghost();
	~Ghost();
	void movement(GLFWwindow *w, double deltatime);

	void addTileToGhost(std::vector<std::vector<GLuint>> tile);
	glm::vec2 translate(double deltaTime);
};