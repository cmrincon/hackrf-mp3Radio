#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>
#include<string.h>


void init_decode(char* file_name, AVCodecContext **codec_ctx, AVFormatContext **fmt_ctx);
void close_decode(AVCodecContext *codec_ctx, AVFormatContext *fmt_ctx);
extern void* decode(void *arg);

//extern unsigned int bufferFreeLen;


struct decoder_args
{
char *file_name;
char *outputbuffer;
};
