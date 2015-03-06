#include <portaudiocpp/PortAudioCpp.hxx>
#include <assert.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <execinfo.h>

#include "Mixer.hpp"
#include "Sound.hpp"

Mixer::Mixer() :
	playing(false), recording(false), tableSize(100), positionInSine(0), lastF(1.f){
	setFrequency(100);
}

Mixer::Mixer(float frequency) :
	playing(false), recording(false), tableSize(100), positionInSine(0), lastF(1.f){
	setFrequency(frequency);
}

int Mixer::PACallback(const void* inputBuffer,
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
		for (unsigned int i = 0; i < framesPerBuffer; i++) {
			float f = (float) sin(((float)positionInSine / tableSize)*M_PI*2.);
			
			float palyBack =  f;
			for (int j = 0; j < nrOfVectors; ++j) {
				palyBack = palyBack + playbackVector[j][vectorPosition];				
			}


			if(vectorPosition == VECTOR_WIDTH){
				vectorPosition = 0; 
			}

			if (lastF > 0 && f < 0) {
				tableSize = nextTableSize;
				positionInSine = 0;
			}

			out[0][i] = palyBack;
			out[1][i] = palyBack;
			positionInSine++;
			lastF = f;

			if (recording) {
				if(recordingPosition <= VECTOR_WIDTH){
					recordingPosition++;
					v[vectorPosition] = f;
				}
			
				if (vectorPosition == startRecordingPosition){
					playbackVector.push_back(v);
					nrOfVectors++;
					std::fill(v.begin(), v.end(), 0);
				}
			}			
			vectorPosition++;	
		}
	} else {
		for (unsigned int i = 0; i < framesPerBuffer; i++){
			out[0][i] = lastF;
			out[1][i] = lastF;
		}
	}

	return paContinue;
}

void Mixer::setFrequency(double freq){
	nextTableSize = Sound::SAMPLE_RATE / freq;
}

void Mixer::startOrStopRecording(bool rec){
	if(rec != recording){
		recording = rec;

		if(rec == false){
			playbackVector.push_back(v);
			nrOfVectors++;
			std::fill(v.begin(), v.end(), 0);			
		}

		if(rec == true){
			startRecordingPosition = vectorPosition;
			v.resize(VECTOR_WIDTH);
			std::fill(v.begin(), v.end(), 0); 
		}
	}

}

double Mixer::getFrequency() {
	return Sound::SAMPLE_RATE / nextTableSize;
}
