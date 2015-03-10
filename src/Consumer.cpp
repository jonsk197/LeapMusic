#include <thread>
#include <chrono>
#include <cstdlib>

#include "LeapListener.hpp"
#include "Consumer.hpp"
#include "Mixer.hpp"
#include "Tutorial.hpp"

Consumer::Consumer(LeapListener& listen, Sound& sound, Tutorial& tutorial) :
	listener(listen), sound(sound), tutorial(tutorial) {
		Entry entry1("Resume" , [](void){
				std::cout << "Menu is open. \n"; });
		menu.addEntry(entry1);

		Entry entry2("Delete last recorded track.", [&](void){
				sound.getMixer().deleteLastTrack(); });
		menu.addEntry(entry2);

		Entry entry3("Add common time.", [&](void){
				sound.getMixer().changeBeatPlaying(); });
		menu.addEntry(entry3);

		Entry entry4("Turn playback on/off", [&](void){
				sound.getMixer().changePlayBack(); });
		menu.addEntry(entry4);

		//Entry entry5("Im fukking done!", [](void){exit(0);});
		//menu.addEntry(entry5);
}

void Consumer::startConsumeLoop() {

	while (true) {
		if(tutorial.isTutorialStillPlaying){
			tutorial.play();
		}

		palmPosition = listener.getPalmPosition();

		sound.getMixer().setVolume((palmPosition.x + 300) / 600);
		sound.getMixer().setToneFromC0(palmPosition.y / 3);

		
		if(listener.menuOpen){
			menu.openOrUpdateMenu(palmPosition);
		} else {
			menu.close();
		}

		// If the user has switched to or from playing a note, tell that
		// to the subsystems. Only tell them on switches.
		if (playingLastFrame != listener.playing){
			playingLastFrame = !playingLastFrame;
			sound.getMixer().playing = playingLastFrame;
		}
		if(recordingLastFrame != listener.recording){
			recordingLastFrame = !recordingLastFrame;
			sound.getMixer().startOrStopRecording(recordingLastFrame);
		}

		std::this_thread::sleep_for (std::chrono::milliseconds(1));
	}
}

void Consumer::threadEntry(LeapListener& listener, Sound& sound, Tutorial& tutorial) {
	Consumer* consumerPointer = new Consumer(listener, sound, tutorial);
	return consumerPointer->startConsumeLoop();
}