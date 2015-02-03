#include "../include/Leap.h"

using namespace Leap;

class Matte{
 public:
  static bool fuzzyEquals(double a, double b, double epsilon);
	static bool fuzzyEquals(Vector a, Vector b, double epsilon);
	static bool fuzzyAngleEquals(Vector a, Vector b, double epsilon);
};
