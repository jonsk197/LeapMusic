#ifndef LEAPMUSIC_CONSUMER
#define LEAPMUSIC_CONSUMER

#include "LeapListener.hpp"

class Consumer{
 public:
	/**
	 * @brief Consumer is a consumer of data from LeapListener.
	 *
	 * @param listen A reference to the instance of LeapListener
	 * from which data is to be consumed.
	 * @return Consumer A new instance of the Consumer class.
	 */
	Consumer(LeapListener& listener);

	/**
	 * @brief Starts the loop which consumes data from the
	 * LeapListener specified in the constructor.
	 */
	void startConsumeLoop();
	static void threadEntry(LeapListener& listener);

 private:
	LeapListener& listener;
	double currentTone;
	bool menuOpen;
	bool playingNote;
	bool recording;
};

#endif
