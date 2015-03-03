#ifndef LEAPMUSIC_CONTINOUS_SINE
#define LEAPMUSIC_CONTINOUS_SINE

#include <portaudiocpp/PortAudioCpp.hxx>
#include <mutex>

class ContinousSine{
 public:
	ContinousSine(float frequency);

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
	double getFrequency();


 private:
	std::mutex tableSizeLock;
	double tableSize;
	int position;
};

#endif
