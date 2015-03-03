#include <portaudiocpp/PortAudioCpp.hxx>
#include <assert.h>
#include <cmath>
#include <iostream>
#include <execinfo.h>

#include "ContinousSine.hpp"
#include "Sound.hpp"

ContinousSine::ContinousSine(float frequency) :
	position(0) {
	setFrequency(frequency);
}

int ContinousSine::PACallback(const void* inputBuffer,
                              void* outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags){
	assert(outputBuffer != NULL);
	(void) timeInfo;
	(void) statusFlags;
	(void) inputBuffer;
	float **out = static_cast<float **>(outputBuffer);


	for (unsigned int i = 0; i < framesPerBuffer; i++){
		std::lock_guard<std::mutex> lock(tableSizeLock);
		float f = (float) sin(((float)position / tableSize)*M_PI*2.);

		out[0][i] = f;
		out[1][i] = f;
		position++;
	}
	return paContinue;
}

void ContinousSine::setFrequency(double freq){
	std::lock_guard<std::mutex> lock(tableSizeLock);
	tableSize = Sound::SAMPLE_RATE / freq;
}

double ContinousSine::getFrequency() {
	std::lock_guard<std::mutex> lock(tableSizeLock);
	return Sound::SAMPLE_RATE / tableSize;
}
