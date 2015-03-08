#ifndef LEAPMUSIC_CONTINOUS_SINE
#define LEAPMUSIC_CONTINOUS_SINE

#include <portaudiocpp/PortAudioCpp.hxx>
#include <mutex>
#include <atomic>

class ContinousSine{
 public:
	ContinousSine(float frequency);
	ContinousSine(void);

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


	void setVolume(double);

	/**
	 * Whether or not the continous sine should be playing.
	 */
	std::atomic<bool> playing;

 private:
	std::atomic<double> nextTableSize;
	std::atomic<double> volume;
	double tableSize;
	int position;
	float lastF;
};

#endif
