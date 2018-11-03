#include "SpaceShip.h"

//Overiding update function
void SpaceShip::update(float deltaTime) {
	//Air Friction	
	if (velocity.x != 0||velocity.y !=0) {
		Vector3 normalizedVelocity = velocity.NormalizeVector();
		frictionForce = Vector3(-75 * normalizedVelocity.x, -75 * normalizedVelocity.y, 0);
		acceleration = force + frictionForce;
	}
	else {
		acceleration = force;
	}
	velocity = velocity + acceleration * deltaTime;
	position = position + velocity * deltaTime;

	updateOutOfScreenPosition();
	updateCenterPoint();
}


/*
	This function decrease the shield value
	@param 
*/
void SpaceShip::decreaseShield(int value) {
	shieldCounts -= value;
	if (shieldCounts == 0) {
		decreaseLive();
		shieldCounts = 4;
	}
}

void SpaceShip::decreaseLive() {
	liveCounts--;
}
