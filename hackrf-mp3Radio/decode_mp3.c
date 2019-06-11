#include "decode_mp3.h"



AVFormatContext *fmt_ctx;
AVCodecContext *codec_ctx;

void init_decode(char* file_name)
{
	const char *url_file = "url = file:";
	const char *url = strncat(&url_file, file_name, sizeof(file_name));
	if(avformat_open_input(fmt_ctx, url, NULL, NULL) < 0) exit(-1);
	if  (avformat_find_stream_info(fmt_ctx, NULL) < 0) exit(-1);

	AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_MP3);
	codec_ctx = avcodec_alloc_context3(codec);
	if (avcodec_open2(codec_ctx,codec,NULL) < 0) exit(-1);



}


unsigned int decode(char * file_name, char * outbuffer, unsigned int bufferlen)
{
	unsigned int ret = 0;
	AVPacket *paket = av_packet_alloc();
	init_decode(file_name);
	//START THE DECODING!



	close_decode();
	av_packet_free(paket);

	return ret;
}
void close_decode()
{
	avformat_close_input(fmt_ctx);
	avcodec_free_context(codec_ctx);

}

