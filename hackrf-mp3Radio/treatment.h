#pragma once
#include"audio.h"
#include<libavformat/avformat.h>
#include "filo.h"
/**
* Data of the stream.
*/
struct dataFormat
{
	unsigned int sampleRate; /** Samplerate of the sample. */
	unsigned int nChannels;/** Number of channels per frame. */
	enum eFormat format; /** Format of the sample */
	unsigned int n_bytes;  /** Number of bytes per sample. */
};
extern struct dataFormat format;

/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void S16_to_int16(filo_ctx *buffer, AVFrame *frame);
/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void S16P_to_int16(filo_ctx *buffer, AVFrame *frame);
/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void S32_to_int32(filo_ctx *buffer, AVFrame *frame);
/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void S32P_to_int32(filo_ctx *buffer, AVFrame *frame);
/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void float_to_float32(filo_ctx *buffer, AVFrame *frame);
/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void floatP_to_float32(filo_ctx *buffer, AVFrame *frame);
/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void double_to_float32(filo_ctx *buffer, AVFrame *frame);
/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void doubleP_to_float32(filo_ctx *buffer, AVFrame *frame);
/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void U8_to_uint8(filo_ctx *buffer, AVFrame *frame);
/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void U8P_to_uint8(filo_ctx *buffer, AVFrame *frame);
/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void S64_to_int32(filo_ctx *buffer, AVFrame *frame);
/**
* Conversion between dataformats and push the data to the buffer using the FIFO module.
*/
void S64P_to_int32(filo_ctx *buffer, AVFrame *frame);

/**
* Return a pointer to one of the treatment functions in function of the frame format.
*/
void (*getFormat(AVFrame *frame))(filo_ctx *buffer, AVFrame *);
