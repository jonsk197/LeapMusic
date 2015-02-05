#include "../include/Leap.h"
#include "Menu.h"
#include <cmath>

using namespace Leap;

bool isOpen = false;
Vector menuCenter;
int menuSize = 50;


void Menu::open(Vector startPosition){
    menuCenter = startPosition;
    updateMenu(startPosition);
}

void Menu::updateMenu(Vector handPosition){

    if(abs(Leap.vec3.distance(menuCenter, handPosition)) > menuSize){
    //do stuff when menuitem is selected
    }
}


