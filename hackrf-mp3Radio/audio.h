#pragma once
#include <portaudio.h>
#include <stdlib.h>

#define FRAMESPERBUFFER 0

enum eFormat
{
	pafloat32,
	paint16,
	paint32,
	paint24,
	paint8,
	pauint8
};
/**
* Initialize the audio resources.
* @param channels Number of channels of the output stream.
* @param format Format of the stream.
* @param sampleRate Sample rate of the stream.
*/
void init_audio(unsigned int channels, enum eFormat format, unsigned int sampleRate);
/**
* It writes to the output stream buffer.
* @param buffer Pointer to the data to write.
* @param n_frames Number of frames of the data. Each frame must contain a sample of each channel.
*/
void audio_write(const void* buffer, unsigned int n_frames);
/**
* Deinitialize the audio resources.
*/
void audio_close();
