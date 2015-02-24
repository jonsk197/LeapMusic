#include "Sound.hpp"
#include "Sine.hpp"

Sound::Sound(){
	int outDevice = sys.defaultOutputDevice().index();
	outParamsBeep = portaudio::DirectionSpecificStreamParameters(
			sys.deviceByIndex(outDevice),
			2, portaudio::FLOAT32,	false,
      sys.deviceByIndex(outDevice).defaultLowOutputLatency(),
      NULL);
}


void Sound::playSine(double length, double frequency){
	int table_size = SAMPLE_RATE / frequency;
	Sine sine(table_size);

	portaudio::StreamParameters
		paramsBeep(portaudio::DirectionSpecificStreamParameters::null(),
							 outParamsBeep, SAMPLE_RATE, 1,
							 paClipOff);
	portaudio::MemFunCallbackStream<Sine>
		streamBeep(paramsBeep, sine, &Sine::generate);

	streamBeep.start();
	sys.sleep(length * 1000);
	streamBeep.stop();
}

float Sound::frequencyOfNoteFromC4(int n){
	return C5 * pow(2, n/12);
}

float Sound::frequencyOfNoteFromC0(int n){
	return C0 * pow(2, n/12);
}
