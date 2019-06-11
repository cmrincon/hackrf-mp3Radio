#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>
#include<string.h>


extern void init_decode(char* file_name);
extern void close_decode();
extern void* decode(void *arg);

extern char* frame_buffer;
extern unsigned int bufferFreeLen;
extern AVFormatContext *fmt_ctx;
extern AVCodecContext *codec_ctx;

Struct decoder_args
{
char *file_name;
char *outputbuffer;
};
