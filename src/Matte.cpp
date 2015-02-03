#include "../include/Leap.h"
#include "Matte.h"

using namespace Leap;



bool Matte::fuzzyEquals(double a, double b, double epsilon){
	return fabs(a - b) < epsilon;
}

bool Matte::fuzzyEquals(Vector a, Vector b, double epsilon){
	Vector diff = a - b;
	return  diff.x < epsilon && diff.y < epsilon && diff.z < epsilon;
}

bool Matte::fuzzyAngleEquals(Vector a, Vector b, double epsilon){
	return a.angleTo(b) < epsilon;
}
