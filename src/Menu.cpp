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
		float angle = Matte::xSignedAngleTo(handPosition, menuCenter, angleUnSigned);

		float angleOfSector = fmodf(2*M_PI, nrOfEntries);
		int sector = (int) (angle/angleOfSector);
		
		std::cout <<  "@@@@@@@@@@@@@@@@@@@" << std::endl << angle << std::endl << "@@@@@@@@@@@@@@@@@@@" << std::endl << angleOfSector << std::endl << "@@@@@@@@@@@@@@@@@@@" << std::endl << sector << std::endl << "@@@@@@@@@@@@@@@@@@@";

		entries.at(sector).select();
	
	}

}

bool Menu::isMenuOpen(){
	return isOpen;
}

