#ifndef LEAPMUSIC_MATTE
#define LEAPMUSIC_MATTE

#include "../include/Leap.h"

using namespace Leap;

class Matte{
 public:
	static bool fuzzyEquals(double a, double b, double epsilon);
	static bool fuzzyEquals(Vector a, Vector b, double epsilon);
	static bool fuzzyAngleEquals(Vector a, Vector b, double epsilon);
	static float xSignedAngleTo(Vector hand, Vector menu, float angle);
	static float linearToDb(float x);
	static float dbToLinear(float db);
	static float xyDistanceTo(Vector hand, Vector menu);
};

#endif
