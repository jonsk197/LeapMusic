#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Graphics.hpp"
#include "GLUtilities.h"
#include "LoadObject.h"


// These initializations are here because C++ sucks.
// They should be in the header file in my opinion.
const vec3 Graphics::cameraPosition = vec3(10.5f, 13.6f, 23.0f);
const vec3 Graphics::cameraTarget = vec3(-10.0f, -10.0f, -10.0f);
const vec3 Graphics::cameraNormal = vec3(0.0f, 1.0f, 0.0f);
const mat4 Graphics::lookMatrix =
	lookAtv(cameraPosition, cameraTarget, cameraNormal);
const mat4 Graphics::transHand = T(0, 0, 0);
const GLfloat Graphics::viewFrustum[] =
	{2.0f*near/(right-left), 0.0f,
	 (right+left)/(right-left), 0.0f,
	 0.0f, 2.0f*near/(top-bottom),
	 (top+bottom)/(top-bottom), 0.0f,
	 0.0f, 0.0f, -(far + near)/(far - near),
	 -2*far*near/(far - near),
	 0.0f, 0.0f, -1.0f, 0.0f };

// The following will be reassigned in initResources.
GLuint Graphics::handProgram = 0;
Model* Graphics::bunny = NULL;

void Graphics::init(int argc, char** argv) {
	int* pargc = &argc;
	glutInit(pargc, argv);
	glutInitContextVersion(3, 2);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Leap Music!");

	std::cout << "Before init" << std::endl;

  // Extension wrangler initialising
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
		std::cout << "Error: " << glewGetErrorString(glew_status) << std::endl;
		exit(11);
  }
	std::cout << "After main loop" << initResources() << std::endl;

	if (true) {
    /* We can display it if everything goes OK */
    glutDisplayFunc(onDisplay);

    glutMainLoop();
  }

	// Upon exiting the main loop;
	freeResources();
}


int Graphics::initResources(void) {
	handProgram = loadShaders("./src/graphics/shaders/hand.vert",
	                          "./src/graphics/shaders/hand.frag");
	bunny = LoadModelPlus("./src/graphics/models/bunnyplus.obj");
	std::cout << "In init" << std::endl;
	glUniformMatrix4fv(glGetUniformLocation(handProgram, "viewFrustum"),
										 1, GL_TRUE, viewFrustum);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutTimerFunc(16, &Graphics::onTimer, 0);
	return 1;
}

void Graphics::onDisplay(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(handProgram);
	drawObject(transHand, bunny, handProgram);
}

void Graphics::freeResources(void) {
	;
}

void Graphics::drawObject(mat4 transform, Model* model, GLuint p) {
	glUniformMatrix4fv(glGetUniformLocation(p, "transform"),
	                   1, GL_TRUE, transform.m);
	DrawModel(model, p, "vertPosition", "vertNormal", "vertTexureCoordinate");
}

void Graphics::onTimer(int value) {
	glutPostRedisplay();
	glutTimerFunc(20, &Graphics::onTimer, value);
}
