#pragma once
#include "Sprite.h"
#include <string>
#include <time.h>
#include <cstdlib>


class Asteroid :public Sprite
{
public:
	//Member function
	Asteroid(std::string fileName): Sprite(fileName){}

	virtual void update(float) = 0;
	virtual void setRadius(float value) {
		radius = value;
	}
};

