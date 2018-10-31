#pragma once
#include "Sprite.h"
#define PI 3.14159265358979

class SpaceShip: public Sprite
{
public:
	//Space ship variables
	const float maxAcceleration;
	int shieldCounts, liveCounts;
	SpaceShip(std::string spriteSheetFilename) :Sprite(spriteSheetFilename), maxAcceleration{ 50 },
		shieldCounts{ 4 }, liveCounts{ 4 } {

	}
	~SpaceShip() {}


	//Member functions
	virtual void update(float);
	void decreaseShield(int);
	void decreaseLive();
};

