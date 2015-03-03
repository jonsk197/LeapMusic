#include <portaudiocpp/PortAudioCpp.hxx>
#include <assert.h>
#include <cmath>
#include <iostream>
#include <execinfo.h>

#include "ContinousSine.hpp"
#include "Sound.hpp"

ContinousSine::ContinousSine(float frequency) :
	playing(false), tableSize(100), position(0), lastF(1.f){
	setFrequency(frequency);
}

int ContinousSine::PACallback(const void* inputBuffer,
                              void* outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags) {
	assert(outputBuffer != NULL);
	(void) timeInfo;
	(void) statusFlags;
	(void) inputBuffer;
	float **out = static_cast<float **>(outputBuffer);

	if (playing) {
		for (unsigned int i = 0; i < framesPerBuffer; i++){
			float f = (float) sin(((float)position / tableSize)*M_PI*2.);

			if (lastF > 0 && f < 0){
				tableSize = nextTableSize;
				position = 0;
			}

			out[0][i] = f;
			out[1][i] = f;
			position++;
			lastF = f;
		}
	} else {
		for (unsigned int i = 0; i < framesPerBuffer; i++){
			out[0][i] = lastF;
			out[1][i] = lastF;
		}
	}
	return paContinue;
}

void ContinousSine::setFrequency(double freq){
	nextTableSize = Sound::SAMPLE_RATE / freq;
}

double ContinousSine::getFrequency() {
	return Sound::SAMPLE_RATE / nextTableSize;
}
