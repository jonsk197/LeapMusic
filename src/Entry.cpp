//
//  Entry.cpp
//  LeapMusic
//
//  Created by Jonas Skog Andersen on 2015-02-06.
//
//

#include "Entry.h"
#include "string"



void Entry::setTitle(std::string str){
	title = str;
}

std::string Entry::getTitle(){
	return title;
}

void Entry::select(){
	selected = true;
}


void Entry::deSelect(){
	selected = false;
}

