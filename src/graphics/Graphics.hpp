#ifndef LEAPMUSIC_GRAPHICS
#define LEAPMUSIC_GRAPHICS

#include <GL/glew.h>

#include "VectorUtils3.h"
#include "LoadObject.h"

class Graphics {
public:
	static void init(int argc, char** argv);
private:
	static int initResources(void);
	static void freeResources(void);
	static void onDisplay(void);
	static void onTimer(int);
	static void drawObject(mat4, Model*, GLuint);

	static GLuint handProgram;
	static Model* bunny;

	static constexpr GLfloat near = 1.0;
	static constexpr GLfloat far = 300.0;
	static constexpr GLfloat right = 0.5;
	static constexpr GLfloat left = -0.5;
	static constexpr GLfloat top = 0.5;
	static constexpr GLfloat bottom = -0.5;
	static const GLfloat viewFrustum[];
  static const vec3 cameraPosition;
  static const vec3 cameraTarget;
	static const vec3 cameraNormal;
  static const mat4 lookMatrix;
	static const mat4 transHand;
};

#endif
