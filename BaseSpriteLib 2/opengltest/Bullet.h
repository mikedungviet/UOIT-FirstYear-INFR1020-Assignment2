#pragma once
#include <string>
#include "Sprite.h"

class Bullet:public Sprite
{
private:
	float lifeTime;
public:
	//Constructor
	Bullet(std::string fileName) 
		:Sprite(fileName), lifeTime{10.0f} {}
	//Copy constructor
	Bullet(const Bullet &defaulCons) : Sprite(defaulCons), lifeTime{defaulCons.lifeTime} {}

	~Bullet();

	//Setters and Getters
	float GetLifeTime() {
		return lifeTime;
	}

	//Member functions
	virtual void Update(float);
protected:
	//Protected Member functions
	void DecreaseLifeTime(float);
};

