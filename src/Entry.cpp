#include <string>

#include "Entry.hpp"

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
