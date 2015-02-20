
#ifndef MENU
#define MENU
#include "../include/Leap.h"
#include "Entry.h"

using namespace Leap;

class Menu{
 public:
	void openOrUpdateMenu(Leap::Vector handPosition);
	bool isMenuOpen();
	float nrOfEntries = 6;
	std::vector<Entry> entries;
	bool isOpen = false;

 private:
	Leap::Vector menuCenter;
	float menuSize = 40;
};

#endif
