#pragma once
#include "Asteroid.h"
#include "Sprite.h"
#include <string>

class SmallAsteroid: public Asteroid {
public:
	SmallAsteroid(std::string fileName):
		Asteroid(fileName) {}
	~SmallAsteroid() {}

	//Member Functions
	virtual void update(float);
};

