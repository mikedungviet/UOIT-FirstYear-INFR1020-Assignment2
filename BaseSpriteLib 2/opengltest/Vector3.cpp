#include "Vector3.h"

/*
	This function calculates the length of a vector
	@return Return the calculated length as a float
*/
float Vector3::GetLength() {
	return sqrt(x * x + y * y + z * z);
}

/*
	This function calculates the normalize vector
	@return Return the dimension as a normalized vector
*/
Vector3 Vector3::NormalizeVector(float length)  {
	return *this / this ->GetLength();
}
