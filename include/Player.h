#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


class Player {
private:
	float x, y;

public:
	Player();
	~Player();
	glm::vec2 movement(GLFWwindow *w);

};