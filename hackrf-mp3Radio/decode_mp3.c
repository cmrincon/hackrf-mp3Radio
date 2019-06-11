#include "decode_mp3.h"

AVCodecContext *codec_ctx;
AVFormatContext *fmt_ctx;
char* frame_buffer;

void init_decode(char* file_name)
{
	int a;
	const char *url_file = "url = file:";
	const char *url = strncat(&url_file, file_name, sizeof(file_name));
	av_register_all();
	fmt_ctx = avformat_alloc_context();
	a = avformat_open_input(&fmt_ctx, file_name, NULL, NULL);
	if ( a < 0)
	{
		printf("Error: %d", a);
		exit(-1);
	}
	if  (avformat_find_stream_info(fmt_ctx, NULL) < 0) exit(-1);

	AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_MP3);
	codec_ctx = avcodec_alloc_context3(codec);
	if (avcodec_open2(codec_ctx,codec,NULL) < 0) exit(-1);

}


void* decode(void *arg)
{
	unsigned int ret = 0;
	unsigned long long a=0;
	AVPacket paket;
	//START THE DECODING!
	av_init_packet(&paket);
	while (av_read_frame(fmt_ctx, &paket) >= 0)
	{
		avformat_flush(fmt_ctx);
	}

	av_packet_free(&paket);

	return ret;
}
void close_decode()
{
	avcodec_free_context(&codec_ctx);
	avformat_close_input(&fmt_ctx);
	
	

}

