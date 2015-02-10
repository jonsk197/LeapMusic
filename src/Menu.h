#ifndef MENU
#define MENU
#include "../include/Leap.h"



class Menu{
 public:
	void open(Leap::Vector startPosition);
	void updateMenu(Leap::Vector handPosition);

	bool isOpen;

 private:
	Leap::Vector menuCenter;
	int menuSize;
};

#endif
