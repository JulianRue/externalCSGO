#include "Math.h"

cMath::cMath() {

}

float cMath::getDistance(Vector *pos1, Vector *pos2) {
	return sqrt(
		pow(double(pos1->x - pos2->x), 2.0) +
		pow(double(pos1->y - pos2->y), 2.0) +
		pow(double(pos1->z - pos2->z), 2.0));
}

float cMath::RandomFloat(float a, float b) {
	return a + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (b - a)));;
}

int cMath::RandomInt(int a, int b) {
	if (b == 0) return 0;
	else {
		int up = rand() % b;
		up += a;
		if (up > b) up = b;
		return up;
	}
}