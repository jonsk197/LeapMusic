#include <thread>
#include <chrono>
#include <cstdlib>

#include "LeapListener.hpp"
#include "Consumer.hpp"
#include "Mixer.hpp"


Consumer::Consumer(LeapListener& listen, Sound& sound, Mixer& mixer) :
	listener(listen), sound(sound), mixer(mixer), playingNote(false) {
		Entry entry1("entry1", [](void){std::cout << "Resume";});
		menu.addEntry(entry1);

		Entry entry2("entry2", [](void){std::cout << "Play sound";});
		menu.addEntry(entry2);

		Entry entry3("entry3", [](void){std::cout << "Change instrument";});
		menu.addEntry(entry3);

		Entry entry4("entry4", [](void){std::cout << "Drop the base";});
		menu.addEntry(entry4);

		Entry entry5("entry5", [](void){std::cout << "Options";});
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

		if(recording != listener.isRecording()){
			recording = !recording;
			mixer.startOrStopRecording(recording);
		}

		currentTone = listener.getFrequency();
		//Implement the mixing part hear. Save the old sine and add it to the other includeing the curentTone.

		sound.getMixer().setFrequency(currentTone);
		std::this_thread::sleep_for (std::chrono::milliseconds(1));
	}
}

void Consumer::threadEntry(LeapListener& listener, Sound& sound, Mixer& mixer) {
	Consumer* consumerPointer = new Consumer(listener, sound, mixer);
	return consumerPointer->startConsumeLoop();
}
