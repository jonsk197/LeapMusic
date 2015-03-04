#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Graphics.hpp"
#include "GLUtilities.h"


// These initializations are here because C++ sucks
const vec3 Graphics::cameraPos = vec3(10.5f, 13.6f, 23.0f);
const vec3 Graphics::cameraTarget = vec3(-10.0f, -10.0f, -10.0f);
const vec3 Graphics::cameraNormal = vec3(0.0f, 1.0f, 0.0f);
const mat4 Graphics::lookMatrix = lookAtv(cameraPos, cameraTarget, cameraNormal);
// This will be reassigned in initResources.
GLuint Graphics::handProgram = 0;


void Graphics::init(int argc, char** argv) {
	int* pargc = &argc;
	glutInit(pargc, argv);
	glutInitContextVersion(3, 2);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Leap Music!");

  // Extension wrangler initialising
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
		std::cout << "Error: " << glewGetErrorString(glew_status) << std::endl;
		exit(11);
  }

	if (initResources()) {
    /* We can display it if everything goes OK */
    glutDisplayFunc(onDisplay);
    glutMainLoop();
  }

	// Upon exiting the main loop;
	freeResources();
}


int Graphics::initResources(void) {
	handProgram = loadShaders("./src/graphics/shaders/hand.vert", "./src/graphics/shaders/hand.frag");

	glClearColor(1.0, 1.0, 1.0, 1.0);
	return 1;
}

void Graphics::onDisplay(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(handProgram);
}

void Graphics::freeResources(void) {
	;
}
