#include <AnimationController.h>

void AnimationController::setanimation(int animationIndex) {
	this->currentAnimation = animationIndex;
}

void AnimationController::step() {
	if (++currentFrame >= animations[currentAnimation].frameCount)
	{
		currentAnimation = animations[currentAnimation].nextAnimation;
		currentFrame = 0;
	}
	int frameIndex = (animations[currentAnimation].startFrame + currentFrame);
	frame[0] = glm::vec2{
		(frameIndex % spritesPerSize.x) * (1.0f / spritesPerSize.x),
		(frameIndex / spritesPerSize.x) * (1.0f / spritesPerSize.x),
	};
	frame[1] = frame[0] + glm::vec2{ spriteSize.x, 0.0f };
	frame[2] = frame[0] + spriteSize;
	frame[3] = frame[0] + glm::vec2{ 0.0f, spriteSize.y };
}

AnimationController::AnimationController(glm::vec3 start, glm::vec3 running) {
	Animation animations[] {
		{start.x, start.y, start.z},
		{running.x, running.y, running.z}
	};
}

const glm::vec2* AnimationController::getFrame() const {
	return frame;
}