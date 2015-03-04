#include <thread>
#include <chrono>
#include <cstdlib>

#include "LeapListener.hpp"
#include "Consumer.hpp"


Consumer::Consumer(LeapListener& listen, Sound& sound) :
	listener(listen), sound(sound), playingNote(false) {
		Entry entry1("entry1", [](void){std::cout << "Resume";});
		menu.addEntry(entry1);

		Entry entry2("entry2", [](void){std::cout << "play sound";});
		menu.addEntry(entry2);

		Entry entry3("entry3", [](void){std::cout << "change instrument";});
		menu.addEntry(entry3);

		Entry entry4("entry4", [](void){std::cout << "Drop the base";});
		menu.addEntry(entry4);

		Entry entry5("entry5", [](void){std::cout << "options";});
		menu.addEntry(entry5);

		Entry entry6("entry6", [](void){exit(0);});
		menu.addEntry(entry6);
}

void Consumer::startConsumeLoop() {
	while (true) {
		menuOpen = listener.getMenuOpen();
		if(menuOpen){
			palmPosition = listener.getPalmPosition();
			menu.openOrUpdateMenu(palmPosition);
		} else{
			menu.closeMenu();
		}

		// If the user has switched to or from playing a note, tell that
		// to the sound system.
		if (playingNote != listener.isPlaying()){
			playingNote = !playingNote;
			sound.getMixer().playing = playingNote;
		}
		recording = listener.isRecording();
		currentTone = listener.getFrequency();
		//Implement the mixing part hear. Save the old sine and add it to the other includeing the curentTone.

		sound.getMixer().setFrequency(currentTone);
		std::this_thread::sleep_for (std::chrono::milliseconds(1));
	}
}

void Consumer::threadEntry(LeapListener& listener, Sound& sound) {
	Consumer* consumerPointer = new Consumer(listener, sound);
	return consumerPointer->startConsumeLoop();
}
