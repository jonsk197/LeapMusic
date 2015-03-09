#ifndef LEAPMUSIC_TUTORIAL
#define LEAPMUSIC_TUTORIAL

#include "../include/Leap.h"

class Tutorial{
 public:
	void play();
	std::atomic<bool>playTutorial {true};

 private:
	
};

#endif
