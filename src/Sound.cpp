#include <math.h>
#include <iostream>

#include "Sound.hpp"
#include "Mixer.hpp"

Sound::Sound() :
	mixer() {
	int outDevice = sys.defaultOutputDevice().index();
	outParamsBeep = portaudio::DirectionSpecificStreamParameters(
			sys.deviceByIndex(outDevice),
			2, portaudio::FLOAT32,	false,
      sys.deviceByIndex(outDevice).defaultLowOutputLatency(),
      NULL);
}


void Sound::playSine(float length, float frequency) {
	mixer.setFrequency(frequency);

	portaudio::StreamParameters
		paramsBeep(portaudio::DirectionSpecificStreamParameters::null(),
							 outParamsBeep, SAMPLE_RATE, FRAMES_PER_BUFFER,
							 paNoFlag);
	portaudio::MemFunCallbackStream<Mixer>
		streamBeep(paramsBeep, mixer, &Mixer::PACallback);

	streamBeep.start();
	sys.sleep(1000 * length);
}


void Sound::threadEntry(Sound& sound) {
	Sound* soundPointer = &sound;
	return soundPointer->startMixer();
}

void Sound::startMixer(void) {
	portaudio::StreamParameters
		paramsBeep(portaudio::DirectionSpecificStreamParameters::null(),
							 outParamsBeep, SAMPLE_RATE, FRAMES_PER_BUFFER,
							 paNoFlag);
	portaudio::MemFunCallbackStream<Mixer>
		streamBeep(paramsBeep, mixer, &Mixer::PACallback);

	streamBeep.start();
	sys.sleep(10000000);
}

double Sound::frequencyOfNoteFromA4(int n){
	return A4 * pow(2, (double)n/12.f);
}

double Sound::frequencyOfNoteFromA4(double f) {
	return C0 * pow(2, f/12.f);
}

double Sound::frequencyOfNoteFromC0(int n) {
	return C0 * pow(2, (double)n/12.f);
}

double Sound::frequencyOfNoteFromC0(double f) {
	return C0 * pow(2, f/12.f);
}


int Sound::toneFromC0(double frequency) {
	return 12 * log(frequency/C0 - 2);
}


Mixer& Sound::getMixer(void) {
	Mixer& ref = mixer;
	return ref;
}

double Sound::handPositionToFrequency(double height){
	return frequencyOfNoteFromC0((height - 10) / 6);
}
