#include "../include/Leap.h"
#include "Menu.h"
#include <cmath>
#include <iostream>

void Menu::open(Leap::Vector startPosition){
	menuCenter = startPosition;
	isOpen = true;
	
}

void Menu::updateMenu(Leap::Vector handPosition){
	
	if(menuCenter.distanceTo(handPosition) > menuSize){
    //do stuff when menuitem is selected
	}
}

void Menu::close(){
	isOpen = false;
}