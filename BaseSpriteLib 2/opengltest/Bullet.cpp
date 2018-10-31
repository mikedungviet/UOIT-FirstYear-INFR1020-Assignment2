#include "Bullet.h"

void Bullet::update(float deltaTime) {
	//Variable

	//Update position
	acceleration = force;
	velocity = velocity + acceleration * deltaTime;
	position = position + velocity * deltaTime;

	//Update position if out of screen
	if (position.y <= -105) {
		position.y = 455;
	}
	if (position.y >= 456) {
		position.y = -104;
	}

	if (position.x >= 1200) {
		position.x = -114;
	}
	if (position.x < -115) {
		position.x = 1199;
	}

	//Update lifetime
	DecreaseLifeTime(deltaTime);
}

void Bullet::DecreaseLifeTime(float deltaTime) {
	lifeTime -= deltaTime;
}