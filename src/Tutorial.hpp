#ifndef LEAPMUSIC_TUTORIAL
#define LEAPMUSIC_TUTORIAL

#include "../include/Leap.h"
#include "Consumer.hpp"


class Tutorial{
 public:
	void play();
	void setPlayTutorial(bool play);
	void listenerPlaying(bool palying);
	void listenerRecording(bool recording);
	void listenerMenuOpen(bool menuOpen);
	void listenerItemSelected(bool itemSelected);

 private:
 	bool starttutorial {true};
	bool listener_Playing {false};
	bool listener_Recording {false};
	bool listener_MenuOpen {false};
	bool listener_ItemSelected {false};
	bool playTutorial {true}; 

};

#endif
