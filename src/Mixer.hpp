#ifndef LEAPMUSIC_MIXER
#define LEAPMUSIC_MIXER

#include <iostream>
#include <portaudiocpp/PortAudioCpp.hxx>
#include <mutex>
#include <atomic>

class Mixer{
 public:
	Mixer(float frequency);

	/**
	 * @brief The function which should be hooked into PortAudio.
	 */
	int PACallback(const void* inputBuffer,
								 void* outputBuffer,
								 unsigned long framesPerBuffer,
								 const PaStreamCallbackTimeInfo* timeInfo,
								 PaStreamCallbackFlags statusFlags);

	/**
	 * @brief Set the frequency the continous Sine should be playing in.
	 *
	 * @param freq A float which should be within the hearable range of
	 * the human ear.
	 */
	void setFrequency(double freq);

	/**
	 * @brief Get the frequency currently playing.
	 *
	 * @return double The frequency.
	 */
	double getFrequency();

	/**
	 * Whether or not the continous sine should be playing.
	 */
	std::atomic<bool> playing;

	/**
	*This vector contains all the voices that has been storied. The voices is is 4 sec long had stories 4*48000k of sample.
	*/

 private:
	std::atomic<double> nextTableSize;
	double tableSize;
	int position;
	float lastF;
};

#endif
