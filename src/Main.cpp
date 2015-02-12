#include <iostream>
#include <string.h>
#include <algorithm>
#include <cmath>

#include "../include/Leap.h"
#include "LeapListener.h"
#include "Matte.h"
#include "Sound.h"



using namespace Leap;

int main(int argc, char** argv) {
	// Create a sample listener and controller
	Menu menu;
	LeapListener listener(menu);
	Controller controller;
	Sound sound;
	sound.playSine(1, 10);

	// Have the sample listener receive events from the controller
	controller.addListener(listener);

	if (argc > 1 && strcmp(argv[1], "--bg") == 0)
		controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

	// Keep this process running until Enter is pressed
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();

	// Remove the sample listener when done
	controller.removeListener(listener);

	return 0;
}
