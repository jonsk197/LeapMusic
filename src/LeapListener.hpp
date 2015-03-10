
#ifndef LEAPMUSIC_LISTENER
#define LEAPMUSIC_LISTENER

#include <string>
#include <atomic>
#include <mutex>

#include "../include/Leap.h"

using namespace Leap;

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Intermediate", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

class LeapListener : public Leap::Listener {
 public:
	LeapListener();

	virtual void onInit(const Controller&);
	virtual void onConnect(const Controller&);
	virtual void onDisconnect(const Controller&);
	virtual void onExit(const Controller&);
	virtual void onFrame(const Controller&);
	virtual void onFocusGained(const Controller&);
	virtual void onFocusLost(const Controller&);
	virtual void onDeviceChange(const Controller&);
	virtual void onServiceConnect(const Controller&);
	virtual void onServiceDisconnect(const Controller&);

	/**
	 * @brief Returns the position of the middle of the palm.
	 *
	 * @return Leap::Vector the position.
	 */
	Vector getPalmPosition();

	std::atomic<bool> menuOpen;
	std::atomic<bool> playing;
	std::atomic<bool> recording;
	std::atomic<float> frequency;

 private:
	const bool DEBUG = false;

	std::mutex palmPositionLock;
	Vector palmPosition;
};

#endif
