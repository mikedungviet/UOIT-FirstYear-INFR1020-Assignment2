#include "SpaceShip.h"

//Overiding update function
void SpaceShip::update(float deltaTime) {

	//Variables
	float resistaceAngle = theta+180;
	const float resistanceForce = 10;
	Vector3 airResistance(0,0,0);
	// physics update goes here!!!!
	acceleration = force; //update new acceleration
	velocity = velocity + acceleration * deltaTime; //update new velocity
	position = position + velocity * deltaTime; //update new position
	Sprite::updateCenterPoint();

	//Check for the bounding box
	Sprite::update(deltaTime);
	
}

/*
	This function decrease the shield value
	@param 
*/
void SpaceShip::decreaseShield(int value) {
	shieldCounts -= value;
}

void SpaceShip::decreaseLive() {
	if (shieldCounts == 0) {
		liveCounts--;
		shieldCounts = 4;
	}
}
