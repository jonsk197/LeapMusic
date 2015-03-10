#ifndef LEAPMUSIC_MIXER
#define LEAPMUSIC_MIXER

#include <iostream>
#include <portaudiocpp/PortAudioCpp.hxx>
#include <mutex>
#include <vector>
#include <atomic>

class Mixer{
 public:
	Mixer(float frequency);
	Mixer();

	/**
	 * @brief The function which should be hooked into PortAudio.
	 */
	int PACallback(const void* inputBuffer,
								 void* outputBuffer,
								 unsigned long framesPerBuffer,
								 const PaStreamCallbackTimeInfo* timeInfo,
								 PaStreamCallbackFlags statusFlags);

	/**
	 * @brief Set the frequency the continous Sine should be playing in.
	 *
	 * @param freq A float which should be within the hearable range of
	 * the human ear.
	 */
	void setFrequency(double freq);

	/**
	 * @brief Set the frequency the continous Sine should be playing in.
	 *
	 * Has the same functionality as setFrequency() but instead plays
	 * tone n counting from C0, the deepest tone to the very left on a
	 * piano.
	 *
	 * @param n The number of steps up from C0 to play.
	 */
	void setToneFromC0(int n);

	/**
	 * @brief Get the frequency currently playing.
	 *
	 * @return double The frequency.
	 */
	double getFrequency();

	/**
	 * Whether or not the mixer should be playing.
	 */
	std::atomic<bool> playing {false};

	/**
	 * Whether or not the mixer should be recodring.
	 */
	std::atomic<bool> recording {false};

	void startOrStopRecording(bool rec);

	void deleteLastTrack();

	void changePlayBack();

	void changeBeatPlaying();

	void setVolume(double);

 private:
	static const int TRACK_NR_SAMPLES = 191999;
	std::atomic<int> nextTone;
	std::atomic<double> volume {1.0};
	std::atomic<bool> playingRecorded {true};
	std::atomic<bool> playingBeat;
	int tone = 0;
	static const int LOWEST_NOTE = 0;
	static const int HIGHEST_NOTE = 60;
	unsigned int positionInSine = 0;
	unsigned int currentTrackPosition = 0;
	unsigned int samplesRecorded = 0;
	unsigned int startRecordingPosition = 0;
	std::vector<float> beatTrack;
	std::vector<float> currentTrack;

	/**
	* This vector contains all the voices that has been stored. The
	* voices are 4 seconds long and stores 4*48000 samples.
	*/
	std::vector<std::vector<float>> playbackVector;
	/**
	* This vector contains lookup tables for all the notes in the
	* western note system. The lookup tables themselves contains
	* precalculated amplitudes together shaping a sinusoidal wave at
	* the frequency the note is at.
	*/
	std::vector<std::vector<float>>	toneLookupTables;
};

#endif
