#include <iostream>
#include <string.h>
#include <cmath>
#include <thread>

#include "../include/Leap.h"
#include "LeapListener.h"
#include "Matte.h"
#include "Sound.h"
#include "Consumer.hpp"

using namespace Leap;

int main(int argc, char** argv) {
	// Create a sample listener and controller
	Menu menu;
	LeapListener listener(menu);
	Controller controller;
	Sound sound;
	sound.playSine(1, 200);	

	/* Have the sample listener receive events from the controller.
	 * It should do nothing more but simply listen and record events
	 * from the device, which can be used in another thread. */
	controller.addListener(listener);

	/* The consumer takes action on the data produced by the
	 * listener. It's responsible for things actually sounding
	 * and appearing on screen. */
	std::thread consumerThread(&Consumer::threadEntry, std::ref(listener));

	if (argc > 1 && strcmp(argv[1], "--bg") == 0)
		controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

	// Keep this process running until Enter is pressed
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();

	// Remove the sample listener when done
	controller.removeListener(listener);

	return 0;
}
