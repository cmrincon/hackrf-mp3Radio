#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>
#include<string.h>
#include <pthread.h>

void init_decode(char* file_name);
void close_decode();
extern unsigned int decode(char *file_name, char *outbuffer, unsigned int bufferlen);