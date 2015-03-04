#ifndef LEAPMUSIC_GRAPHICS
#define LEAPMUSIC_GRAPHICS

#include <GL/glew.h>

#include "VectorUtils3.h"

class Graphics {
public:
	static void init(int argc, char** argv);
private:
	static int initResources(void);
	static void freeResources(void);
	static void onDisplay(void);

	static GLuint handProgram;

	static constexpr GLfloat near = 1.0;
	static constexpr GLfloat far = 300.0;
	static constexpr GLfloat right = 0.5;
	static constexpr GLfloat left = -0.5;
	static constexpr GLfloat top = 0.5;
	static constexpr GLfloat bottom = -0.5;
	static constexpr 	GLfloat viewFrustum[] =
		{2.0f*near/(right-left), 0.0f,
		 (right+left)/(right-left), 0.0f,
		 0.0f, 2.0f*near/(top-bottom),
		 (top+bottom)/(top-bottom), 0.0f,
		 0.0f, 0.0f, -(far + near)/(far - near),
		 -2*far*near/(far - near),
		 0.0f, 0.0f, -1.0f, 0.0f };
  static const vec3 cameraPos;
  static const vec3 cameraTarget;
	static const vec3 cameraNormal;
  static const mat4 lookMatrix;
};

#endif
