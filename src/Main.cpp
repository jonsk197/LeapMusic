#include <iostream>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>

#include "../include/Leap.h"
#include "LeapListener.hpp"
#include "Matte.hpp"
#include "Sound.hpp"
#include "Mixer.hpp"
#include "Consumer.hpp"
#include "Tutorial.hpp"

int main(int argc, char** argv) {
	// Create a sample listener and controller
	Controller controller;
	Sound sound;
	LeapListener listener;
	Tutorial tutorial;

		/* Have the sample listener receive events from the controller.
	 * It should do nothing more but simply listen and record events
	 * from the device, which can be used in another thread. */
	controller.addListener(listener);

	/* The thread which plays a continous sine wave. */
	std::thread soundThread(&Sound::MixerThreadEntry,
													std::ref(sound));

	/* The consumer takes action on the data produced by the
	 * listener. It's responsible for things actually sounding
	 * and appearing on screen. */
	std::thread consumerThread(&Consumer::threadEntry,
														 std::ref(listener), std::ref(sound), std::ref(tutorial));

	if (argc > 1 && strcmp(argv[1], "--bg") == 0)
		controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

	// Keep this process running until Enter is pressed
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();

	// Remove the sample listener when done
	controller.removeListener(listener);

	return 0;
}
