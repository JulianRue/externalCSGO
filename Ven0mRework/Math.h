#ifndef MATH_H
#define MATH_H

#define WIN32_LEAN_AND_MEAN
#include "Classid.h"

#include <windows.h>
#include <string>
#include <iostream>

class cMath {
protected:

public:
	cMath();

	struct Vector {
		float x, y, z;
	};

	struct VectorXY {
		float x, y;
	};

	float getDistance(Vector *pos1, Vector *pos2);
	float RandomFloat(float a, float b);
	int RandomInt(int a, int b);

public:

private:

};

#endif