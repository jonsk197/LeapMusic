#ifndef LEAPMUSIC_ENTRY
#define LEAPMUSIC_ENTRY

#include <string>

#include "../include/Leap.h"

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
