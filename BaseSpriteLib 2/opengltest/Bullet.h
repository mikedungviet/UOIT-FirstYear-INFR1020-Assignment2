#pragma once
#include "Sprite.h"
#include <string>

class Bullet:public Sprite
{
private:
	float lifeTime;
public:
	//Constructor
	Bullet(std::string fileName) 
		:Sprite(fileName), lifeTime{2.0f} {}

	~Bullet() {}

	//Setters and Getters
	float GetLifeTime() {
		return lifeTime;
	}

	//Member functions
	virtual void update(float);
protected:
	//Protected Member functions
	void DecreaseLifeTime(float);
};

