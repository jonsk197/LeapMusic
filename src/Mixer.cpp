#include <portaudiocpp/PortAudioCpp.hxx>
#include <assert.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream> 
#include <iterator>
#include <stdlib.h>
#include <stdio.h>

#include "Mixer.hpp"
#include "Sound.hpp"
#include "sndfile.h"

Mixer::Mixer(float frequency) :
  beatTrack(TRACK_NR_SAMPLES, 0),
	currentTrack(TRACK_NR_SAMPLES, 0) {
	setFrequency(frequency);

	int i = 0;
	for (float j = 0; j <= 1; j += 0.005) {
		beatTrack.at(0 	    + i) = j;
		beatTrack.at(46000  + i) = j;
		beatTrack.at(96000  + i) = j;
		beatTrack.at(144000 + i) = j;
		i++;
	}
	for (float k = 1; k >= 0; k -= 0.005) {
		beatTrack.at(0      + i) = k;
		beatTrack.at(46000  + i) = k;
		beatTrack.at(96000  + i) = k;
		beatTrack.at(144000 + i) = k;
		i++;
	}

	// There are ~ 100 notes between A0 and A8
	for (int tone = 0; tone < 100; tone++ ) {
		double frequency = Sound::frequencyOfNoteFromC0(tone);
		double tableSize = Sound::SAMPLE_RATE / frequency;
		std::vector<float> table(ceil(tableSize), 0);
		for (int position = 0; position < tableSize; position++) {
			table[position] = (float) sin(((double)position / tableSize)*M_PI*2.);
		}
		toneLookupTables.push_back(table);
	}
}

Mixer::Mixer() : Mixer(Sound::A4) {}


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

	for (unsigned int i = 0; i < framesPerBuffer; i++) {
		float amplitude = 0;

		if (playing) {
			positionInSine++;
			if (positionInSine >= toneLookupTables.at(tone).size())
				positionInSine = 0;

			amplitude += toneLookupTables[tone].at(positionInSine)*volume;

			if(recording) {
				samplesRecorded++;
				if(samplesRecorded >= TRACK_NR_SAMPLES)
					samplesRecorded = 0;

				currentTrack[currentTrackPosition] = amplitude;

				if (currentTrackPosition == startRecordingPosition){
					playbackVector.push_back(currentTrack);
					samplesRecorded = 0;
					std::fill(currentTrack.begin(), currentTrack.end(), 0);
				}
			}
		}

		if (playingBeat)
			amplitude += beatTrack[currentTrackPosition];

		if (playingRecorded) {
			for (unsigned int j = 0; j < playbackVector.size(); ++j) {
				amplitude = amplitude + playbackVector[j][currentTrackPosition];
			}
		}

		if(currentTrackPosition == TRACK_NR_SAMPLES){
			currentTrackPosition = 0;
		}else{
			currentTrackPosition++;
		}
		if (toneLookupTables[tone][positionInSine] < 0 &&
				toneLookupTables[tone][positionInSine - 1] > 0 ) {	
			positionInSine = 0;
			tone = nextTone;
		}
		out[0][i] = amplitude;
		out[1][i] = amplitude;
	}
	return paContinue;
}

void Mixer::setFrequency(double freq) {
	nextTone = Sound::toneFromC0(freq);
}

void Mixer::setToneFromC0(int n) {
	if (n <= lowerBoundaryHandPosition){
		nextTone = lowerBoundaryHandPosition;
	}else{
		if (n >= upperBoundaryHandPosition){
			nextTone = upperBoundaryHandPosition;
		}else{
			nextTone =n;
		}
	}
}

void Mixer::startOrStopRecording(bool rec) {
	if(rec != recording){
		recording = rec;

		if(rec == false) {
			playbackVector.push_back(currentTrack);
			std::fill(currentTrack.begin(), currentTrack.end(), 0);
		}
		else
			startRecordingPosition = currentTrackPosition;
	}
}

void Mixer::deleteLastTrack() {
	if (playbackVector.size() >= 1) {
		playbackVector.pop_back();
	}
}

void Mixer::changePlayBack() {
	playingRecorded = !playingRecorded;
}

void Mixer::changeBeatPlaying() {
	playingBeat = !playingBeat;
}
double Mixer::getFrequency() {
	return Sound::frequencyOfNoteFromC0(tone);
}

void Mixer::setVolume(double vol) {
	if (vol >= 0.0 && vol <= 1.0)
		volume = vol;
}

void Mixer::readFile(const std::string& strFilename) {
	std::cout << "Start read" << std::endl;

	std::ifstream iStream (strFilename, std::ifstream::binary);

	if (iStream) {
		// get length of file:
		iStream.seekg (0, iStream.end);
		int length = iStream.tellg();
		iStream.seekg (0, iStream.beg);
		char * buffer = new char [length];

		// read data as a block:
		iStream.read (buffer,length);
		audioFile.resize(length);

		for(int i =0; i<= length; i++){
		audioFile[i] = buffer[i]*0.1f;
		std::cout << audioFile[i]  << " ,";
		}

		if (iStream)
		  std::cout << "all characters read successfully." << std::endl;
		else
			std::cout << "error: only " << iStream.gcount() << " could be read." << std::endl;

		iStream.close();
	}
}
