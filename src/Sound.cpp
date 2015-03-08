#include <math.h>
#include <iostream>

#include "Sound.hpp"
#include "Mixer.hpp"

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
							 paNoFlag);
	portaudio::MemFunCallbackStream<Mixer>
		streamBeep(paramsBeep, sine, &Mixer::PACallback);

	streamBeep.start();
	sys.sleep(1000 * length);
}


void Sound::MixerThreadEntry(Sound& sound) {
	Sound* soundPointer = &sound;
	return soundPointer->startMixer();
}

void Sound::startMixer(void) {
	portaudio::StreamParameters
		paramsBeep(portaudio::DirectionSpecificStreamParameters::null(),
							 outParamsBeep, SAMPLE_RATE, FRAMES_PER_BUFFER,
							 paNoFlag);
	portaudio::MemFunCallbackStream<Mixer>
		streamBeep(paramsBeep, sine, &Mixer::PACallback);

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


int Sound::toneFromC0(double frequency) {
	return 2 * log(frequency/C0 - 2);
}


Mixer& Sound::getMixer(void) {
	Mixer& s = sine;
	return s;
}

double Sound::handPositionToFrequency(double height){
	return frequencyOfNoteFromC0((height - 10) / 6);
}
