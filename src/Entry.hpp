#ifndef LEAPMUSIC_ENTRY
#define LEAPMUSIC_ENTRY

#include <string>

#include "../include/Leap.h"

using namespace Leap;

class Entry{
public:
	Entry(std::string name, std::function<void(void)> activateFunction);
	void setTitle(std::string str);
	std::string getTitle();
	std::function<void(void)> activateFunction;
private:
	std::string title;
};

#endif
