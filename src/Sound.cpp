#include <math.h>
#include <iostream>

#include "Sound.hpp"
#include "ContinousSine.hpp"

Sound::Sound() :
	sine(Sound::A4) {
	int outDevice = sys.defaultOutputDevice().index();
	outParamsBeep = portaudio::DirectionSpecificStreamParameters(
			sys.deviceByIndex(outDevice),
			2, portaudio::FLOAT32,	false,
      sys.deviceByIndex(outDevice).defaultLowOutputLatency(),
      NULL);
}


void Sound::playSine(float length, float frequency) {
	sine.setFrequency(frequency);

	portaudio::StreamParameters
		paramsBeep(portaudio::DirectionSpecificStreamParameters::null(),
							 outParamsBeep, SAMPLE_RATE, FRAMES_PER_BUFFER,
							 paClipOff);
	portaudio::MemFunCallbackStream<ContinousSine>
		streamBeep(paramsBeep, sine, &ContinousSine::PACallback);

	streamBeep.start();
	sys.sleep(1000 * length);
}


void Sound::continousSineThreadEntry(Sound& sound) {
	Sound* soundPointer = &sound;
	return soundPointer->startContinousSine();
}

void Sound::startContinousSine(void) {
	portaudio::StreamParameters
		paramsBeep(portaudio::DirectionSpecificStreamParameters::null(),
							 outParamsBeep, SAMPLE_RATE, FRAMES_PER_BUFFER,
							 paClipOff);
	portaudio::MemFunCallbackStream<ContinousSine>
		streamBeep(paramsBeep, sine, &ContinousSine::PACallback);

	streamBeep.start();
	sys.sleep(10000000);
}

double Sound::frequencyOfNoteFromA4(int n){
	return A4 * pow(2, n/12);
}

double Sound::frequencyOfNoteFromA4(double f) {
	return C0 * pow(2, f/12.f);
}

double Sound::frequencyOfNoteFromC0(int n) {
	return C0 * pow(2, n/12);
}

double Sound::frequencyOfNoteFromC0(double f) {
	return C0 * pow(2, f/12.f);
}

ContinousSine& Sound::getContinousSine(void) {
	ContinousSine& s = sine;
	return s;
}

double Sound::handPositionToFrequency(double height){
	return frequencyOfNoteFromC0((height - 10) / 6);
}
