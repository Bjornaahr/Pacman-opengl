#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "gameobject.h"


class Player : public GameObject{
private:
	glm::vec2 direction;
	float x, y;
	float rotate;

public:
	Player();
	~Player();
	void movement(GLFWwindow *w, bool coll);

	float rotation();

	glm::vec2 translate(double deltaTime);

};