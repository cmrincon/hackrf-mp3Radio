#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>

void init_decode(char* file_name);
int get_mp3_frame(FILE *fd,char *frame,unsigned short *size);
unsigned int decode(char *file_name, char *outbuffer, unsigned int bufferlen);