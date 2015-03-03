#include <thread>
#include <chrono>

#include "LeapListener.hpp"
#include "Consumer.hpp"

Consumer::Consumer(LeapListener& listen, Sound& sound) :
	listener(listen), sound(sound) {}

void Consumer::startConsumeLoop() {
	while (true) {
		menuOpen = listener.getMenuOpen();
		if(menuOpen){
			palmPosition = listener.getPalmPosition();
			menu.openOrUpdateMenu(palmPosition);

		} else{
			menu.closeMenu();
		}
		currentTone = listener.getTone();
		playingNote = listener.isPlaying();
		recording = listener.isRecording();
		currentTone = listener.getFrequency();
		sound.getContinousSine().setFrequency(currentTone);
		std::this_thread::sleep_for (std::chrono::milliseconds(1));
	}
}

void Consumer::threadEntry(LeapListener& listener, Sound& sound) {
	Consumer* consumerPointer = new Consumer(listener, sound);
	return consumerPointer->startConsumeLoop();
}
