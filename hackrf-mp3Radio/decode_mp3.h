#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>
#include<string.h>
#include <time.h>
#include <unistd.h> 
#include "treatment.h"



struct decoder_args
{
	char *file_name;
};
int parser(enum AVSampleFormat input_format, unsigned long pa_format);
int init_decode(char* file_name, AVCodecContext **codec_ctx, AVFormatContext **fmt_ctx, int *stream_index);
void close_decode(AVCodecContext *codec_ctx, AVFormatContext *fmt_ctx);
extern void* decode(const char *arg);
void treat_packet(AVFrame *frame);


//extern unsigned int bufferFreeLen;





