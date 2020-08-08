#pragma once
#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>
#include<string.h>
#include <time.h>
#include <unistd.h> 
#include "treatment.h"



typedef struct decoder_args_t
{
	char *file_name;
	filo_ctx *outputBuffer;
}decoder_args;

/**
* Open the input file and initilize de decoder resources.
* @param file_name Name of the file to open.
* @param codec_ctx Decoder context.
* @param fmt_ctx Decoder format.
* @param stream_index Index.
*/
int init_decode(char* file_name, AVCodecContext **codec_ctx, AVFormatContext **fmt_ctx, int *stream_index);
/**
* Close the resources of the decoder.
*/
void close_decode(AVCodecContext *codec_ctx, AVFormatContext *fmt_ctx);
/**
* Function which can be run in a thread. It uses the FIFO module to push the output of the decoder.
* @param arg Name of the mp3 file.
*/
extern void* decode(decoder_args args);
void treat_packet(AVFrame *frame);






