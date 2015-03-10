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
		beatTrack.at(48000  + i) = j;
		beatTrack.at(96000  + i) = j;
		beatTrack.at(144000 + i) = j;
		i++;
	}
	for (float k = 1; k >= 0; k -= 0.005) {
		beatTrack.at(0      + i) = k;
		beatTrack.at(48000  + i) = k;
		beatTrack.at(96000  + i) = k;
		beatTrack.at(144000 + i) = k;
		i++;
	}

	// There are ~ 100 notes between A0 and A8, we only want flat ones.
	i = 0;
	int sharpsInARow = 2;
	bool twoLastTime = true;
	for (int tone = 0; tone < 100; tone++ ) {
		i++;
		// Every other not is not a flat note, except for every 11th.
		if (i % 2 == 0) {
			if (sharpsInARow == 0){
				i++;
				if (twoLastTime){
					sharpsInARow = 3;
					twoLastTime = false;
				}
				else{
					sharpsInARow = 2;
					twoLastTime = true;
				}
			}
			else {
				sharpsInARow--;
				continue;
			}
		}
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

			amplitude += toneLookupTables[tone].at(positionInSine) * volume;

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
				amplitude += playbackVector[j][currentTrackPosition];
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

		// Clipping
		amplitude = fmin(amplitude, 1.0f);
		amplitude = fmax(amplitude, -1.0f);
		// Output
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
