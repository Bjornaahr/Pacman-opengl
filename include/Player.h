#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "gameobject.h"


class Player : public GameObject{
private:
	float x, y;
	float rotate;
	bool direction[4];

public:
	Player();
	~Player();
	glm::vec2 movement(GLFWwindow *w, double DeltaTime);

	float rotation();

};