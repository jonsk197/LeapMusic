
#ifndef LeapMusic_Menu
#define LeapMusic_Menu
#include "../include/Leap.h"
#include "Entry.h"

using namespace Leap;

class Menu{
 public:
	void openOrUpdateMenu(Leap::Vector handPosition);
	bool isMenuOpen();
	float nrOfEntries = 4;
	std::vector<Entry> entries;
	bool isOpen = false;

 private:
	Leap::Vector menuCenter;
	float menuSize = 25;
};

#endif
