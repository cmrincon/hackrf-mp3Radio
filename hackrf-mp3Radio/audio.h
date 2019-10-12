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

void init_audio(unsigned int channels, enum eFormat format, unsigned int sampleRate);
void audio_write(const void* buffer, unsigned int n_frames);
void audio_close();
