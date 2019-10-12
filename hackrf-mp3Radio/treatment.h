#pragma once
#include"audio.h"
#include<libavformat/avformat.h>
#include "fifo.h"

struct dataFormat
{
	unsigned int sampleRate;
	unsigned int nChannels;
	enum eFormat format;
	unsigned int n_bytes;
};
extern struct dataFormat format;

void S16_to_int16(AVFrame *frame);
void S16P_to_int16(AVFrame *frame);
void S32_to_int32(AVFrame *frame);
void S32P_to_int32(AVFrame *frame);
void float_to_float32(AVFrame *frame);
void floatP_to_float32(AVFrame *frame);
void double_to_float32(AVFrame *frame);
void doubleP_to_float32(AVFrame *frame);
void U8_to_uint8(AVFrame *frame);
void U8P_to_uint8(AVFrame *frame);
void S64_to_int32(AVFrame *frame);
void S64P_to_int32(AVFrame *frame);
int getFormat(AVFrame *frame, void (**treatment_func)(AVFrame*));
