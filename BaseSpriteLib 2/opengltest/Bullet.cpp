#include "Bullet.h"

void Bullet::Update(float deltaTime) {
	//Variable

	//Update position
	acceleration = force;
	velocity = velocity + acceleration * deltaTime;
	position = position + velocity * deltaTime;

	//Update position if out of screen
	
	//Update lifetime
	DecreaseLifeTime(deltaTime);
}

void Bullet::DecreaseLifeTime(float deltaTime) {
	lifeTime -= deltaTime;
}