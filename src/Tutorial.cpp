#include <cmath>

#include "Tutorial.hpp"
#include "Consumer.hpp"
#include "../include/Leap.h"

using namespace Leap;

void Tutorial::play(){

	if(isTutorialStillPlaying){
		if(playSound){
			stepPlaying();
			if (consumer.playing){
				playSound = false;
				recordingSound = true;
			}
		}

		if(recordingSound){
			stepRecording();
			if(consumer.recording){
				recordingSound=false;
				menuOpen = true;
			}
		}	

		if(menuOpen){
			stepOpenMenu();
			if(consumer.menuOpen){
				turnTutorialOnorOff();
			}
		}
	}
}

void Tutorial::turnTutorialOnorOff(){
	isTutorialStillPlaying = !isTutorialStillPlaying;
}

void Tutorial::stepPlaying(){
	std::cout << "Hi, this is Leap Music. To play a sound, shut your hand with all fingers except the forefinger." << std::endl;
	/*
	* Kod för att köra bild och ljud för detta event.
	*/
	return;
}

void Tutorial::stepRecording(){
	std::cout << "Good, if you want to record the sound shut all fingers of the hand, even the forefinger." << std::endl;
	/*
	* Kod för att köra bild och ljud för detta event.
	*/
	return;

}

void Tutorial::stepOpenMenu(){
	std::cout << "Open menu by turning the hand 180 degrees to the right or left." << std::endl; 
	/*
	* Kod för att köra bild och ljud för detta event.
	*/
	return;
}

void Tutorial::stepSelectItem(){
	std::cout << "Select the menu item by move your hand to the item you want to select." << std::endl; 
	/*
	* Kod för att köra bild och ljud för detta event.
	*/
	return;
}