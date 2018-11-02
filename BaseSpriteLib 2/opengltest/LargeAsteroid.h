#pragma once
#include "Asteroid.h"
class LargeAsteroid : public Asteroid
{
public:
	LargeAsteroid(std::string fileName): Asteroid(fileName){}
	~LargeAsteroid();

	virtual void update(float);
};

