#include <assert.h>
#include <cmath>

#include "Sine.h"

Sine::Sine(int tableSize) :
	tableSize_(tableSize), leftPhase_(0), rightPhase_(0)
{
  table_ = new float[tableSize];
  for (int i = 0; i < tableSize; ++i) {
      table_[i] = 0.25f * (float)sin(((double)i/(double)tableSize)*M_PI*2.);
    }
}

Sine::~Sine(){
  delete[] table_;
}

int Sine::generate(const void *inputBuffer,
			    void *outputBuffer,
			    unsigned long framesPerBuffer,
			    const PaStreamCallbackTimeInfo *timeInfo,
			    PaStreamCallbackFlags statusFlags){
  assert(outputBuffer != NULL);

  float **out = static_cast<float **>(outputBuffer);

  for (unsigned int i = 0; i < framesPerBuffer; ++i)
    {
      out[0][i] = table_[leftPhase_];
      out[1][i] = table_[rightPhase_];

      leftPhase_ += 1;
      if (leftPhase_ >= tableSize_)
	leftPhase_ -= tableSize_;

      rightPhase_ += 3;
      if (rightPhase_ >= tableSize_)
	rightPhase_ -= tableSize_;
    }

  return paContinue;
}
