#include <cmath>

#include "Tutorial.hpp"
#include "Mixer.hpp"
#include "Consumer.hpp"

void Tutorial::play(){
	
	if(playTutorial){

		if(starttutorial){
			std::cout << "Hi, this is Leap Music. To play a sound, shut your hand with all fingers except the forefinger." << std::endl;
			/*
			* Kod för att köra bild och ljud för detta event.
			*/
		}

		if(listener_Playing){
			std::cout << "Good, if you want to record the sound shut all fingers of the hand, even the forefinger." << std::endl;
			/*
			* Kod för att köra bild och ljud för detta event.
			*/
		}	
		
		if(listener_MenuOpen){
			std::cout << "Open menu by turning the hand 180 degrees to the right or left." << std::endl; 
			/*
			* Kod för att köra bild och ljud för detta event.
			*/
		}
		
		if(listener_ItemSelected){
			std::cout << "Select the menu item by move your hand to the item you want to select." << std::endl; 
			/*
			* Kod för att köra bild och ljud för detta event.
			*/
		}	

		setPlayTutorial(false);
	}
}


void Tutorial::listenerPlaying(bool playing){
	listener_Playing = playing;
	play();
}

void Tutorial::listenerRecording(bool recording){
	listener_Recording = recording;
	play();
}

void Tutorial::listenerMenuOpen(bool menuOpen){
	listener_MenuOpen = menuOpen;
	play();
}

void Tutorial::listenerItemSelected(bool itemSelected){
	listener_ItemSelected = itemSelected;
	play();
}

void Tutorial::setPlayTutorial(bool play){
	playTutorial = play;
}
