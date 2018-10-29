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


	// this should be collisions here!  
	// but for this example, just checking if we are at a particular pixel location on Y is fine....
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
