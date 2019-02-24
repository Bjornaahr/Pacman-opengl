#include "gameobject.h"
#include <iostream>

GameObject::GameObject()
	: Position(0, 0), Size(1, 1), Color(0.0f), Rotation(0.0f), Sprite() { }
//Set attributes of gameobject with specified values
GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color)
	: Position(pos), Size(size), Color(color), Rotation(0.0f), Sprite(sprite) { }
//Draw gameobject
void GameObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}