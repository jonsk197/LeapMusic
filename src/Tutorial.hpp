#ifndef LEAPMUSIC_TUTORIAL
#define LEAPMUSIC_TUTORIAL

#include "Consumer.hpp"
#include "LeapListener.hpp"
#include <atomic>

#include "../include/Leap.h"

class Tutorial{
 public:

 	Tutorial(LeapListener& listener);
	
	void play();
	void turnTutorialOnOrOff();
	std::atomic<bool>isTutorialStillPlaying {true};

 private:
 	void stepPlaying();
 	void stepRecording();
 	void stepOpenMenu();
 	void stepSelectItem();

  	LeapListener& listener;
  	bool runOnce = true;
 	bool playSound = true;
	bool recordingSound = false;
	bool menuOpenTT = false;
};

#endif
