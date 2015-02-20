#include "LeapListener.h"
#include "Consumer.hpp"

#include <thread>

Consumer::Consumer(LeapListener& listen) : listener(listen) {
}

void Consumer::startConsumeLoop() {
	while (true) {
		menuOpen = listener.getMenuOpen();
		currentTone = listener.getTone();
		playingNote = listener.isPlaying();
		recording = listener.isRecording();
	}
}

void Consumer::threadEntry(LeapListener& listener) {
	Consumer* consumerPointer = new Consumer(listener);
	return consumerPointer->startConsumeLoop();
}
