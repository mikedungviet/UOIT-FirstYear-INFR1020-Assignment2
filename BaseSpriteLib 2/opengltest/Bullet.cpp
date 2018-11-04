#include "Bullet.h"

void Bullet::update(float deltaTime) {
	//Update position if out of screen
	Sprite::update(deltaTime);
	
	//Update lifetime
	DecreaseLifeTime(deltaTime);
}

void Bullet::DecreaseLifeTime(float deltaTime) {
	lifeTime -= deltaTime;
}
