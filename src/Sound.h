#ifndef LEAPMUSIC_SOUND
#define LEAPMUSIC_SOUND

#include "portaudiocpp/PortAudioCpp.hxx"

class Sound{
 public:
	/**
	 * @brief Plays a sound with the form of a sinusoidal wave to
	 * the selected sound card of the computer.
	 *
	 * @param length For how long in seconds the tone should be played.
	 * @param frequency The frequency of the tone.
	 */
	void playSine(double length, double frequency);
	Sound();

 private:
	static constexpr double SAMPLE_RATE = 44100.0f;
  static const int FRAMES_PER_BUFFER = 64;
  portaudio::AutoSystem autoSys;
	portaudio::System& sys = portaudio::System::instance();
	portaudio::DirectionSpecificStreamParameters outParamsBeep;
};

#endif
