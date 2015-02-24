#include <thread>

#include "LeapListener.hpp"
#include "Consumer.hpp"

Consumer::Consumer(LeapListener& listen) : listener(listen) {}

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
		std::this_thread::yield();
	}
}

void Consumer::threadEntry(LeapListener& listener) {
	Consumer* consumerPointer = new Consumer(listener);
	return consumerPointer->startConsumeLoop();
}
