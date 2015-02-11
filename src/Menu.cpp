#include "../include/Leap.h"
#include "Menu.h"
#include <cmath>
#include <iostream>

void Menu::openOrUpdateMenu(Leap::Vector handPosition){
	
	if (!isOpen) {
		menuCenter = handPosition;
	}
	isOpen = true;
	
	if(menuCenter.distanceTo(handPosition) > menuSize){
		float angel = handPosition.angleTo(Leap::Vector (0,1,0));
		float angelOfSector = fmod(2*M_PI,nrOfEntries);
		float sector = fmodf(angel, angelOfSector);
		
		//Need to fix this vector.
		//entries.at(sector).select();
		
	}
}

bool Menu::isMenuOpen(){
	return isOpen;
}

