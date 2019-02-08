#pragma once

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Player {
public:
	Player();
	~Player();
private:
	void Movement();
};