#pragma once
#include <cmath>
class Vector3
{
public:
	Vector3() {}
	Vector3(float X, float Y, float Z) :x(X), y(Y), z(Z) {
	
	}
	~Vector3() {}


	/*
		This function sets the values for vectors
	*/
	void set(float X, float Y, float Z) {
		x = X;
		y = Y;
		z = Z;
	}

	void set(Vector3 anotherVec) {
		x = anotherVec.x;
		y = anotherVec.y;
		z = anotherVec.z;
	}

	// operator overloading
	// this is just scalar multiplication
	Vector3 operator*(const float scalar) const
	{
		Vector3 result;
		result.x = x * scalar;
		result.y = y * scalar;
		result.z = z * scalar;
		return result;
	}

	// this is the addition operator to add two vectors
	Vector3 operator+(const Vector3 rhs) const
	{
		Vector3 result;
		result.x = x + rhs.x;
		result.y = y + rhs.y;
		result.z = z + rhs.z;

		return result;
	}

	/*
		This function divides a vector with a scalar
		@param const scalar The magnitude to be divided by
		@return Returns the result
	*/
	Vector3 operator/ (const float scalar) const {
		Vector3 result;
		result.x = x / scalar;
		result.y = y / scalar;
		result.z = z / scalar;
		return result;
	}

	Vector3 operator- (const Vector3 rhs) const {
		Vector3 result;
		result.x = x - rhs.x;
		result.y = y - rhs.y;
		result.z = z - rhs.z;
		return result;
	}

	bool operator!=(const float value) {
		if (x == value && y != value) {
			return true;
		}
		return false;
	}

	//Member Functions
	float GetLength();
	Vector3 NormalizeVector();

	// its a 3D vector, here is the data!
	float x, y, z;

};

