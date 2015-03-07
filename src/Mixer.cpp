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
	commonTime.resize(VECTOR_WIDTH);
	std::fill(commonTime.begin(), commonTime.end(), 0);
	
	int i = 0;
	for (float j = 0 ; j <= 1; j = j +0.005){

		commonTime.at(0 	 + i) = j;
		commonTime.at(46000  + i) = j;
		commonTime.at(96000  + i) = j;
		commonTime.at(144000 + i) = j;
		i++;
	}

	for (float k = 1; k >= 0; k = k - 0.005){
		commonTime.at(0 	 + i) = k;
		commonTime.at(46000  + i) = k;
		commonTime.at(96000  + i) = k;
		commonTime.at(144000 + i) = k;
		i++;
	}
}

Mixer::Mixer(float frequency) :
	playing(false), recording(false), tableSize(100), positionInSine(0), lastF(1.f){
	setFrequency(frequency);
	commonTime.resize(VECTOR_WIDTH);
	std::fill(commonTime.begin(), commonTime.end(), 0);
	
	int i = 0;
	for (float j = 0 ; j <= 1; j = j +0.005){

		commonTime.at(0 	 + i) = j;
		commonTime.at(46000  + i) = j;
		commonTime.at(96000  + i) = j;
		commonTime.at(144000 + i) = j;
		i++;
	}

	for (float k = 1; k >= 0; k = k - 0.005){
		commonTime.at(0 	 + i) = k;
		commonTime.at(46000  + i) = k;
		commonTime.at(96000  + i) = k;
		commonTime.at(144000 + i) = k;
		i++;
	}
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

	if (true) {
		for (unsigned int i = 0; i < framesPerBuffer; i++) {
			float f = (float) sin(((float)positionInSine / tableSize)*M_PI*2.);
			float playBack = 0;

			if(playing){
				playBack = playBack + f;
			}

			if (playingBeat){
				playBack = playBack + commonTime[vectorPosition];
			}

			if (playBackBool && vectorPosition >= 1){
				for (int j = 0; j < nrOfVectors; ++j) {
					playBack = playBack + playbackVector[j][vectorPosition];				
				}
			}

			if (recording) {
				if(recordingPosition <= VECTOR_WIDTH){
					recordingPosition++;
					v.at(vectorPosition) = f;
				}
			}

			if(vectorPosition == VECTOR_WIDTH){
				vectorPosition = 0; 
			}else{
				vectorPosition++;
			}

			if (lastF > 0 && f < 0) {
				tableSize = nextTableSize;
				positionInSine = 0;
			}

			out[0][i] = playBack;
			out[1][i] = playBack;
			positionInSine++;
			lastF = f;

		
			if (recording) {
				if (vectorPosition == startRecordingPosition){
					playbackVector.push_back(v);
					recordingPosition = 0;
					nrOfVectors++;
					std::fill(v.begin(), v.end(), 0);
				}
			}				
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

void Mixer::deleteLastTrack(){
	if (nrOfVectors > 1){
		playbackVector.pop_back();
		nrOfVectors--;
	}
}

void Mixer::changePlayBack(){
	playBackBool = !playBackBool;
}

void Mixer::changeBeatPlaying(){
	playingBeat = !playingBeat;
}
double Mixer::getFrequency() {
	return Sound::SAMPLE_RATE / nextTableSize;
}
