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
	 * @brief Get the frequency currently playing.
	 *
	 * @return double The frequency.
	 */
	double getFrequency();

	/**
	 * Whether or not the mixer should be playing.
	 */
	std::atomic<bool> playing;

	/**
	 * Whether or not the mixer should be recodring.
	 */
	std::atomic<bool> recording;

	/**
	*This vector contains all the voices that has been storied. The voices is is 4 sec long had stories 4*48000k of sample.
	*/
	std::vector< std::vector<float> > playbackVector;

	void startOrStopRecording(bool rec);

	void deleteLastTrack();

	void changePlayBack();

	void changeBeatPlaying();

 private:
	std::atomic<double> nextTableSize;
	std::atomic<bool> playBackBool;
	std::atomic<bool> playingBeat;
	double tableSize;
	int positionInSine;
	int vectorPosition = 0;
	int recordingPosition = 0;
	int startRecordingPosition = 0;
	float lastF;
	static constexpr float VECTOR_WIDTH = 191999;
	float nrOfVectors = 0;
	std::vector<float> commonTime;
	std::vector<float> v; 

};

#endif
