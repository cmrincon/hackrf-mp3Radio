#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>
#include<string.h>
#include <unistd.h> 



void init_decode(char* file_name, AVCodecContext **codec_ctx, AVFormatContext **fmt_ctx, int *stream_index);
void close_decode(AVCodecContext *codec_ctx, AVFormatContext *fmt_ctx);
extern void* decode(void *arg);
void treat_packet(AVFrame *frame,uint8_t *buffer, struct struc_mutex *mutex);


//extern unsigned int bufferFreeLen;

struct struc_mutex
{
	pthread_mutex_t lock;
	pthread_cond_t cond_empty;
	pthread_cond_t cond_full;
	uint8_t* read_ptr;
	uint8_t* write_ptr;
};

struct decoder_args
{
char *file_name;
uint8_t *outputbuffer;
struct struc_mutex *mutex;
};

