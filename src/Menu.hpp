#ifndef LEAPMUSIC_MENU
#define LEAPMUSIC_MENU

#include "../include/Leap.h"
#include "Entry.hpp"

class Menu{
 public:
	void openOrUpdateMenu(Leap::Vector handPosition);
	void closeMenu();
	std::vector<Entry> entries;
	bool isOpen = false;

 private:
	const float MENU_SIZE = 25;
	float nrOfEntries;
	Leap::Vector menuCenter;
};

#endif
