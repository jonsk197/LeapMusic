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

	/**
	 * @brief Returns the frequency of a musical note with an offset n
	 * from C4.
	 *
	 * @param n The number of notes, positive or negative, the desired
	 * note is from C4.
	 * @return float The frequency of the note.
	 */
	float frequencyOfNoteFromC4(int n);

	/**
	 * Here follows the definition of the frequency of every musical
	 * note in the european scale as a C++ float const.
	 */
	const float C0 =  16.35f;
	const float Cs0 = 17.32f;
	const float Db0 = 17.32f;
	const float D0 =  18.35f;
	const float Ds0 = 19.45f;
	const float Eb0 = 19.45f;
	const float E0 =  20.60f;
	const float F0 =  21.83f;
	const float Fs0 = 23.12f;
	const float Gb0 = 23.12f;
	const float G0 =  24.50f;
	const float Gs0 = 25.96f;
	const float Ab0 = 25.96f;
	const float A0 =  27.50f;
	const float As0 = 29.14f;
	const float Bb0 = 29.14f;
	const float B0 =  30.87f;
	const float C1 =  32.70f;
	const float Cs1 = 34.65f;
	const float Db1 = 34.65f;
	const float D1 =  36.71f;
	const float Ds1 = 38.89f;
	const float Eb1 = 38.89f;
	const float E1 =  41.20f;
	const float F1 =  43.65f;
	const float Fs1 = 46.25f;
	const float Gb1 = 46.25f;
	const float G1 =  49.00f;
	const float Gs1 = 51.91f;
	const float Ab1 = 51.91f;
	const float A1 =  55.00f;
	const float As1 = 58.27f;
	const float Bb1 = 58.27f;
	const float B1 =  61.74f;
	const float C2 =  65.41f;
	const float Cs2 = 69.30f;
	const float Db2 = 69.30f;
	const float D2 =  73.42f;
	const float Ds2 = 77.78f;
	const float Eb2 = 77.78f;
	const float E2 =  82.41f;
	const float F2 =  87.31f;
	const float Fs2 = 92.50f;
	const float Gb2 = 92.50f;
	const float G2 =  98.00f;
	const float Gs2 = 103.83f;
	const float Ab2 = 103.83f;
	const float A2 =  110.00f;
	const float As2 = 116.54f;
	const float Bb2 = 116.54f;
	const float B2 =  123.47f;
	const float C3 =  130.81f;
	const float Cs3 = 138.59f;
	const float Db3 = 138.59f;
	const float D3 =  146.83f;
	const float Ds3 = 155.56f;
	const float Eb3 =  155.56f;
	const float E3 =  164.81f;
	const float F3 =  174.61f;
	const float Fs3 = 185.00f;
	const float Gb3 = 185.00f;
	const float G3 =  196.00f;
	const float Gs3 = 207.65f;
	const float Ab3 = 207.65f;
	const float A3 =  220.00f;
	const float As3 = 233.08f;
	const float Bb3 = 233.08f;
	const float B3 =  246.94f;
	const float C4 =  261.63f;
	const float Cs4 = 277.18f;
	const float Db4 = 277.18f;
	const float D4 =  293.66f;
	const float Ds4 = 311.13f;
	const float Eb4 = 311.13f;
	const float E4 =  329.63f;
	const float F4 =  349.23f;
	const float Fs4 = 369.99f;
	const float Gb4 = 369.99f;
	const float G4 =  392.00f;
	const float Gs4 = 415.30f;
	const float Ab4 = 415.30f;
	const float A4 =  440.00f;
	const float As4 = 466.16f;
	const float Bb4 = 466.16f;
	const float B4 =  493.88f;
	const float C5 =  523.25f;
	const float Cs5 = 554.37f;
	const float Db5 = 554.37f;
	const float D5 =  587.33f;
	const float Ds5 = 622.25f;
	const float Eb5 = 622.25f;
	const float E5 =  659.25f;
	const float F5 =  698.46f;
	const float Fs5 = 739.99f;
	const float Gb5 = 739.99f;
	const float G5 =  783.99f;
	const float Gs5 = 830.61f;
	const float Ab5 = 830.61f;
	const float A5 =  880.00f;
	const float As5 = 932.33f;
	const float Bb5 = 932.33f;
	const float B5 =  987.77f;
	const float C6 =  1046.50f;
	const float Cs6 = 1108.73f;
	const float Db6 = 1108.73f;
	const float D6 =  1174.66f;
	const float Ds6 = 1244.51f;
	const float Eb6 = 1244.51f;
	const float E6 =  1318.51f;
	const float F6 =  1396.91f;
	const float Fs6 = 1479.98f;
	const float Gb6 = 1479.98f;
	const float G6 =  1567.98f;
	const float Gs6 = 1661.22f;
	const float Ab6 = 1661.22f;
	const float A6 =  1760.00f;
	const float As6 = 1864.66f;
	const float Bb6 = 1864.66f;
	const float B6 =  1975.53f;
	const float C7 =  2093.00f;
	const float Cs7 = 2217.46f;
	const float Db7 = 2217.46f;
	const float D7 =  2349.32f;
	const float Ds7 = 2489.02f;
	const float Eb7 = 2489.02f;
	const float E7 =  2637.02f;
	const float F7 =  2793.83f;
	const float Fs7 = 2959.96f;
	const float Gb7 = 2959.96f;
	const float G7 =  3135.96f;
	const float Gs7 = 3322.44f;
	const float Ab7 = 3322.44f;
	const float A7 =  3520.00f;
	const float As7 = 3729.31f;
	const float Bb7 = 3729.31f;
	const float B7 =  3951.07f;
	const float C8 =  4186.01f;
	const float Cs8 = 4434.92f;
	const float Db8 = 4434.92f;
	const float D8 =  4698.63f;
	const float Ds8 = 4978.03f;
	const float Eb8 = 4978.03f;
	const float E8 =  5274.04f;
	const float F8 =  5587.65f;
	const float Fs8 = 5919.91f;
	const float Gb8 = 5919.91f;
	const float G8 =  6271.93f;
	const float Gs8 = 6644.88f;
	const float Ab8 = 6644.88f;
	const float A8 =  7040.00f;
	const float As8 = 7458.62f;
	const float Bb8 = 7458.62f;
	const float B8 =  7902.13f;


 private:
	static constexpr double SAMPLE_RATE = 48000.0f;
  static const int FRAMES_PER_BUFFER = 64;
  portaudio::AutoSystem autoSys;
	portaudio::System& sys = portaudio::System::instance();
	portaudio::DirectionSpecificStreamParameters outParamsBeep;
};

#endif
