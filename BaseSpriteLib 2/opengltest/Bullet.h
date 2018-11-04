#pragma once
#include "Sprite.h"
#include <string>
#include <iostream>

class Bullet:public Sprite
{
private:
	float lifeTime;
public:
	//Constructor
	Bullet(std::string fileName) 
		:Sprite(fileName), lifeTime{2.5f} {}

	~Bullet() {}

	//Setters and Getters
	float GetLifeTime() {
		return lifeTime;
	}

	//Member functions
	virtual void update(float);
	//virtual bool checkIfCollide(Sprite *);
protected:
	//Protected Member functions
	void DecreaseLifeTime(float);
};

