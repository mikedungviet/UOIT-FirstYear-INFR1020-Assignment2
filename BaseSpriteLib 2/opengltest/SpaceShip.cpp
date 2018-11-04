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
	}
}

void SpaceShip::decreaseLive() {
	liveCounts--;
}
