#include <thread>
#include <chrono>
#include <cstdlib>

#include "LeapListener.hpp"
#include "Consumer.hpp"
#include "Mixer.hpp"


Consumer::Consumer(LeapListener& listen, Sound& sound) :
	listener(listen), sound(sound), playingNote(false), recording(false) {
		Entry entry1("TechnoViking: 'All heil das'." , [](void){std::cout << "TechnoViking: 'All heil das'." << std::endl; });
		menu.addEntry(entry1);

		Entry entry2("DEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEL", [&](void){ sound.getMixer().deleteLastTrack(); });
		menu.addEntry(entry2);

		Entry entry3("Add common time.", [&](void){ sound.getMixer().changeBeatPlaying(); });
		menu.addEntry(entry3);

		Entry entry4("Turn playback on/off", [&](void){ sound.getMixer().changePlayBack(); });
		menu.addEntry(entry4);

		//Entry entry5("Im fukking done!", [](void){exit(0);});
		//menu.addEntry(entry5);
}

void Consumer::startConsumeLoop() {
	while (true) {
		menuOpen = listener.menuOpen;
		palmPosition = listener.getPalmPosition();
		if(menuOpen){
			menu.openOrUpdateMenu(palmPosition);
		} else{
			menu.close();
		}

		// If the user has switched to or from playing a note, tell that
		// to the sound system.
		if (playingNote != listener.playing){
			playingNote = !playingNote;
			sound.getMixer().playing = playingNote;
		}

		if(recording != listener.recording){
			recording = !recording;
			sound.getMixer().startOrStopRecording(recording);
		}
		
		recording = listener.recording;
		sound.getMixer().setToneFromC0(palmPosition.y / 3);
		std::this_thread::sleep_for (std::chrono::milliseconds(1));
	}
}

void Consumer::threadEntry(LeapListener& listener, Sound& sound) {
	Consumer* consumerPointer = new Consumer(listener, sound);
	return consumerPointer->startConsumeLoop();
}
