#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class AnimationController {
private:
	struct Animation {
		int startFrame, frameCount, nextAnimation;
	};
	Animation * animations;
	glm::vec2 frame[4];
	int currentFrame, currentAnimation, frameCount;
	glm::ivec2 spritesPerSize;
	glm::vec2 spriteSize;
public:
	AnimationController(int frameCount, glm::ivec2 spritesPerSize, Animation animations[]) :
		currentFrame(0),
		currentAnimation(0),
		frameCount(frameCount),
		spritesPerSize(spritesPerSize),
		spriteSize({ 1.0f / spritesPerSize.x, 1.0f / spritesPerSize.y }),
		animations(animations)
	{
		frame[0] = { 0, 0 };
		frame[1] = { spriteSize.x, 0.0f };
		frame[2] = spriteSize;
		frame[3] = { 0.0f, spriteSize.y };
	}
	AnimationController(glm::vec3 star, glm::vec3 running);

	void setanimation(int animationIndex);
	void step();
	const glm::vec2* getFrame() const;
};

/*
Animation animations[] = {
	{0, 5, 1}, //start run
	{5, 8, 1}, //running
};
AnimationController anim(13, { 4, 4 }, animations);

frame[4] for uv's
*/