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

	if(menuCenter.distanceTo(handPosition) > MENU_SIZE){

		float angleUnSigned = (handPosition - menuCenter).angleTo(Leap::Vector (0,1,0));
		float angleDeg = Matte::xSignedAngleTo(handPosition, menuCenter, angleUnSigned);

		int angleOfSectorDeg = (int)(360/nrOfEntries);
		int sector = (int) (angleDeg/angleOfSectorDeg);

		std::cout <<  "@@@@@@@@@@@@@@@@@@@" << std::endl << angleDeg << std::endl << "@@@@@@@@@@@@@@@@@@@" << std::endl << angleOfSectorDeg << std::endl << "@@@@@@@@@@@@@@@@@@@" << std::endl << sector << std::endl << "@@@@@@@@@@@@@@@@@@@";

		entries.at(sector).select();

	}

}

bool Menu::isMenuOpen(){
	return isOpen;
}
