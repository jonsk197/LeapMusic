#ifndef LEAPMUSIC_TUTORIAL
#define LEAPMUSIC_TUTORIAL

#include "../include/Leap.h"
#include "Consumer.hpp"

class Tutorial{
 public:
	void play();
	void turnTutorialOnorOff();
	std::atomic<bool>isTutorialStillPlaying {true};

 private:
 	void stepPlaying();
 	void stepRecording();
 	void stepOpenMenu();
 	void stepSelectItem();

  	Consumer& consumer;
 	bool playSound = true;
	bool recordingSound = false;
	bool menuOpen = false;
};

#endif
