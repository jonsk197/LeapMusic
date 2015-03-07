#ifndef LEAPMUSIC_GRAPHICS
#define LEAPMUSIC_GRAPHICS

#include <atomic>

#include <GL/glew.h>

#include "VectorUtils3.h"
#include "LoadObject.h"

class Graphics {
public:
	static void init(int argc, char** argv);

	static std::atomic<float> handX;
	static std::atomic<float> handY;

private:
	static int initResources(void);
	static void freeResources(void);
	static void onDisplay(void);
	static void onTimer(int);
	static void drawObject(mat4, Model*, GLuint);

	static GLuint program;
	static GLuint grass;
	static Model* bunny;
	static mat4   transHand;

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
};

#endif
