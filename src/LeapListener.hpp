#ifndef LEAPMUSIC_LISTENER
#define LEAPMUSIC_LISTENER

#include <string>
#include <mutex>

#include "../include/Leap.h"

using namespace Leap;

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Intermediate", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

class LeapListener : public Leap::Listener {
 public:
	// Because we have a mutex which is nonmovable
	// we must redefine the copy constructor and assignment.
	LeapListener(LeapListener const&);
	LeapListener& operator=(const LeapListener& rhs);

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
	 * @brief Gets whether or not the menu is open in the
	 * listener.
	 *
	 * @return bool True if the menu is open.
	 */
	bool getMenuOpen();

	/**
	 * @brief Whether the player wants to output a tone or not.
	 *
	 * @return bool True if the player wants to play a tone.
	 */
	bool isPlaying();

	/**
	 * @brief Whether the player wants to record a tone or not.
	 *
	 * @return bool True if the player wants to record.
	 */
	bool isRecording();

	/**
	 * @brief Returns the frequency for the hand position.
	 *
	 * @return a vector with the handposition.
	 */
	float getFrequency();


	/**
	 * @brief Returns the hand position.
	 *
	 * @return a float with the db for the frequency.
	 */
	Vector getPalmPosition();

 private:
	std::mutex menuLock;
	bool menuOpen;

	std::mutex recordPlayingLock;
	bool playing;
	bool recording;

	std::mutex frequencyLock;
	float frequency;

	std::mutex palmPositionLock;
	Vector palmPosition;

	const bool DEBUG = false;
};

#endif
