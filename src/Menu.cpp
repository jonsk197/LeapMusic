#include "../include/Leap.h"
#include "Menu.h"
#include "Sound.h"
#include "Matte.h"

#include <cmath>
#include <iostream>


using namespace Leap;

void Menu::openOrUpdateMenu(Leap::Vector handPosition){

	if (!isOpen) {
		menuCenter = handPosition;
	}
	isOpen = true;

	// std::cout <<  "@@@@@@@@@@@@@@@@@@@" << std::endl << menuCenter.distanceTo(handPosition) << std::endl << "@@@@@@@@@@@@@@@@@@@" << std::endl << menuCenter << std::endl << "@@@@@@@@@@@@@@@@@@@" << std::endl << handPosition << std::endl << "@@@@@@@@@@@@@@@@@@@";

	if(menuCenter.distanceTo(handPosition) > menuSize){
		
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

