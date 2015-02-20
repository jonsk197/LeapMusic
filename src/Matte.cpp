#include "../include/Leap.h"
#include "Matte.h"

#include <cmath>

using namespace Leap;

/**
 * Returns true if a and b are within epsilon of each other.
 */
bool Matte::fuzzyEquals(double a, double b, double epsilon){
	return fabs(a - b) < epsilon;
}

/**
 * Returns true if every element of the vectors a and b are within
 * epsilon of each other.
 */
bool Matte::fuzzyEquals(Vector a, Vector b, double epsilon){
	Vector diff = a - b;
	return  diff.x < epsilon && diff.y < epsilon && diff.z < epsilon;
}

/**
 * Returns true if the smallest angle betwene the two vectors are
 * within epsilon of each other.
 */
bool Matte::fuzzyAngleEquals(Vector a, Vector b, double epsilon){
	return a.angleTo(b) < epsilon;
}

float Matte::xSignedAngleTo(Vector hand, Vector menu, float angle){

	if(hand.x - menu.x > 0){
		return angle*(180/M_PI);
	}else{
		return (2*M_PI - angle)*(180/M_PI);
	}	
}