#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


class Player {
private:

public:
	Player();
	~Player();
	void movement(GLFWwindow *w, glm::vec2 *position);

};