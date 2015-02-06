#include "../include/Leap.h"
#include "Menu.h"
#include <cmath>

void Menu::open(Leap::Vector startPosition){
    menuCenter = startPosition;
}

void Menu::updateMenu(Leap::Vector handPosition){

    if(menuCenter.distanceTo(handPosition) > menuSize){
    //do stuff when menuitem is selected
    }
}
