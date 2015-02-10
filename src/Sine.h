#ifndef LEAPMUSIC_SINE
#define LEAPMUSIC_SINE

#include <math.h>
#include <assert.h>

#include "portaudiocpp/PortAudioCpp.hxx"

class Sine{
 public:
	Sine(int tableSize);
	~Sine();

	int generate(const void *inputBuffer,
		     void *outputBuffer,
		     unsigned long framesPerBuffer,
		     const PaStreamCallbackTimeInfo *timeInfo,
		     PaStreamCallbackFlags statusFlags);

 private:
	float *table_;
	int tableSize_;
	int leftPhase_;
	int rightPhase_;
};

#endif
