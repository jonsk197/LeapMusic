#include <iostream>
#include <string.h>
#include "../include/Leap.h"
#include "LeapListener.h"
#include "Matte.h"
#include "EventHandler.h"
#include <algorithm>
#include <cmath>
#include <thread>


using namespace Leap;

void event_thread(Menu& menu) {
	EventHandler::checkForEvent(menu);
}


int main(int argc, char** argv) {
	// Create a sample listener and controller
	Menu menu;
	LeapListener listener(menu);
	Controller controller;
	
	std::thread eventThread(event_thread, menu);
	eventThread.join();

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
