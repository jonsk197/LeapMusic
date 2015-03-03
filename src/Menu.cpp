#include <cmath>
#include <iostream>

#include "../include/Leap.h"
#include "Menu.hpp"
#include "Sound.hpp"
#include "Matte.hpp"

using namespace Leap;

void Menu::openOrUpdateMenu(Leap::Vector handPosition){

	if (!isOpen) {
		menuCenter = handPosition;
	}
	isOpen = true;


	if( Matte::xyDistanceTo(menuCenter, handPosition) > MENU_SIZE){

		float angleUnSigned = (handPosition - menuCenter).angleTo(Leap::Vector (0,1,0));
		float angleDeg = Matte::xSignedAngleTo(handPosition, menuCenter, angleUnSigned);

		int angleOfSectorDeg = (int)(360/nrOfEntries);
		int sector = (int) (angleDeg/angleOfSectorDeg);

		entries.at(sector).select();

	}
}

void Menu::closeMenu(){
	 isOpen =false;
}
