#include "Asteroid.h"

void Asteroid::update(float deltaTime) {
	position = position + velocity * deltaTime;
	Sprite::updateOutOfScreenPosition();
	Sprite::updateCenterPoint();
}