#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>
#include<string.h>


void init_decode(char* file_name);
void close_decode();
extern unsigned int decode();

extern char* frame_buffer;
extern unsigned int bufferFreeLen;
extern AVFormatContext *fmt_ctx;
extern AVCodecContext *codec_ctx;
