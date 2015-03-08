#include <string>

#include "Entry.hpp"

Entry::Entry(std::string name,std::function<void(void)> activateFunction) :
	activateFunction(activateFunction), title(name) {
}

void Entry::setTitle(std::string str){
	title = str;
}

std::string Entry::getTitle(){
	return title;
}
