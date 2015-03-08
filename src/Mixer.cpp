#include <portaudiocpp/PortAudioCpp.hxx>
#include <assert.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>

#include "Mixer.hpp"
#include "Sound.hpp"


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
		std::cout << "lolo: " << tone << '\n';
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
		positionInSine++;
		float amplitude = 0;

		if (playing) {
			std::cout << tone << std::endl;
			if (positionInSine >= toneLookupTables.at(tone).size())
				positionInSine = 0;

			amplitude += toneLookupTables[tone].at(positionInSine);

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

		if (toneLookupTables[tone][positionInSine] > 0 &&
				toneLookupTables[tone][positionInSine - 1] < 0 ) {
			tone = nextTone;
			positionInSine = 0;
		}
		out[0][i] = amplitude;
		out[1][i] = amplitude;
	}
	return paContinue;
}

void Mixer::setFrequency(double freq) {
	nextTone = Sound::toneFromC0(freq);
	std::cout << "frequency: " << freq << " tone: " << nextTone << '\n';
}

void Mixer::setToneFromC0(int n) {
	nextTone = n;
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
