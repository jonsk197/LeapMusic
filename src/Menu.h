#ifndef MENU
#define MENU
#include "../include/Leap.h"

class Menu{
 public:
	void open(Leap::Vector startPosition);
	void updateMenu(Leap::Vector handPosition);
    void close();
	bool isOpen;

 private:
	Leap::Vector menuCenter;
	int menuSize;
};

#endif
