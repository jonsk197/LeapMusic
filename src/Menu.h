
#ifndef MENU
#define MENU
#include "../include/Leap.h"

using namespace Leap;

class Menu{
 public:
	void openOrUpdateMenu(Leap::Vector handPosition);
	bool isMenuOpen();
	Vector<Entry> entries;
	float nrOfEntries = 6;
	bool isOpen = false;

 private:
	Leap::Vector menuCenter;
	int menuSize;
};

#endif
