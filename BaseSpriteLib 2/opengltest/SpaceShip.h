#pragma once
#include "Sprite.h"
#define PI 3.14159265358979

class SpaceShip: public Sprite
{
public:
	//Space ship variables
	int shieldCounts, liveCounts;
	Vector3 frictionForce;

	SpaceShip(std::string spriteSheetFilename) :Sprite(spriteSheetFilename),
		shieldCounts{ 4 }, liveCounts{ 4 } {}
	~SpaceShip() {}


	//Member functions
	void decreaseShield(int);
	void decreaseLive();
};

