#include "Sound.h"
#include "Sine.h"

Sound::Sound(){
	int outDevice = sys.defaultOutputDevice().index();
	outParamsBeep = portaudio::DirectionSpecificStreamParameters(
			sys.deviceByIndex(outDevice),
			2, portaudio::FLOAT32,	false,
      sys.deviceByIndex(outDevice).defaultLowOutputLatency(),
      NULL);
}


void Sound::playSine(double length, double frequency){
	Sine sine(100);

	portaudio::StreamParameters
		paramsBeep(portaudio::DirectionSpecificStreamParameters::null(),
							 outParamsBeep, SAMPLE_RATE, 1,
							 paClipOff);
	portaudio::MemFunCallbackStream<Sine>
		streamBeep(paramsBeep, sine, &Sine::generate);

	streamBeep.start();
	sys.sleep(length * 1000);
	streamBeep.stop();
	streamBeep.close();
}
