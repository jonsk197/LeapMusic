#ifndef LeapMusic_Entry_H
#define LeapMusic_Entry_H
#include "../include/Leap.h"
#include <string>


using namespace Leap;

class Entry{
public:
	std::string title = "";
	bool selected = false;
	void setTitle(std::string str);
	std::string getTitle();
	void select();
	void deSelect();
private:
};

#endif
