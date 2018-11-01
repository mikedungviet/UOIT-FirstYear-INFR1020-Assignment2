#include "SmallAsteroid.h"

void SmallAsteroid::update(float deltaTime) {
	
	position = position + velocity * deltaTime;
	Sprite::update(deltaTime);

}
