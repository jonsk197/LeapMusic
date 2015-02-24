#include <iostream>
#include <string>
#include <cmath>
#include <thread>

#include "../include/Leap.h"
#include "LeapListener.hpp"
#include "Matte.hpp"
#include "Sound.hpp"
#include "Consumer.hpp"

int main(int argc, char** argv) {
	// Create a sample listener and controller
	LeapListener listener;
	Controller controller;
	Sound sound;

	// Lille katt
	sound.playSine(0.25, Sound::C5);
	sound.playSine(0.25, Sound::D5);
	sound.playSine(0.5, Sound::E5);

	sound.playSine(0.25, Sound::C5);
	sound.playSine(0.25, Sound::D5);
	sound.playSine(0.5, Sound::E5);

	sound.playSine(0.25, 659);
	sound.playSine(0.25, 783);
	sound.playSine(0.25, 698);
	sound.playSine(0.25, 659);
	sound.playSine(0.25, 698);
	sound.playSine(0.25, 659);
	sound.playSine(0.25, 587);

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
