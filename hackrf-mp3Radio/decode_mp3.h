#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>
#include<string.h>

#include <unistd.h> 
#include "fifo.h"

struct decoder_args
{
	char *file_name;
};

void init_decode(char* file_name, AVCodecContext **codec_ctx, AVFormatContext **fmt_ctx, int *stream_index);
void close_decode(AVCodecContext *codec_ctx, AVFormatContext *fmt_ctx);
extern void* decode(void *arg);
void treat_packet(AVFrame *frame);


//extern unsigned int bufferFreeLen;





