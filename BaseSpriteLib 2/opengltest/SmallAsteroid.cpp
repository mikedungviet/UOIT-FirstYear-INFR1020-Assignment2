#include "SmallAsteroid.h"

void SmallAsteroid::update(float deltaTime) {
	
	position = position + velocity * deltaTime;
	Sprite::updateOutOfScreenPosition();
	Sprite::updateCenterPoint();

}

