#include "SpaceShip.h"

/*
	This function decrease the shield value
	@param 
*/
void SpaceShip::decreaseShield(int value) {
	shieldCounts -= value;
	if (shieldCounts <= 0) {
		decreaseLive();
		shieldCounts = 4;
		position.set(900, 450, 0);
		velocity.set(0, 0, 0);
	}
}

void SpaceShip::decreaseLive() {
	liveCounts--;
}
