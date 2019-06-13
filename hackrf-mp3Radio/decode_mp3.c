#include "decode_mp3.h"


char* frame_buffer;


void init_decode(char* file_name, AVCodecContext **codec_ctx, AVFormatContext **fmt_ctx, int *stream_index)
{
	int a;
	av_register_all();
	*fmt_ctx = avformat_alloc_context();
	a = avformat_open_input(fmt_ctx, file_name, NULL, NULL);
	if ( a < 0)
	{
		printf("Error: %d", a);
		exit(-1);
	}
	if  (avformat_find_stream_info(*fmt_ctx, NULL) < 0) exit(-1);
	*stream_index = av_find_best_stream(*fmt_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_MP3);
	*codec_ctx = avcodec_alloc_context3(codec);
	if (avcodec_open2(*codec_ctx,codec,NULL) < 0) exit(-1);
	
}


void* decode(void *arg)
{
	int ret = 0, stream_idx=0;
	AVCodecContext *codec_ctx = NULL;
	AVFormatContext *fmt_ctx = NULL;
	AVPacket packet;
	AVFrame *frame;
	struct decoder_args *thread_args = (struct decoder_args *) arg;
	//INIT DECODE
	av_init_packet(&packet);
	frame = av_frame_alloc();
	init_decode(thread_args->file_name, &codec_ctx, &fmt_ctx,&stream_idx);
	

	//START THE DECODING!
	while (av_read_frame(fmt_ctx, &packet) >= 0)
	{
		if (packet.stream_index == stream_idx)
		{
			if ((ret = avcodec_send_packet(codec_ctx, &packet)) < 0)
			{
				printf("ERROR\n");
				//exit(-1);
			}
			if (avcodec_receive_frame(codec_ctx, frame) != 0)
			{
				printf("ERROR\n");
				//exit(-1);
			}
			treat_packet(frame);
		}
	}
	av_frame_free(&frame);
	close_decode(codec_ctx, fmt_ctx);
	return ret;
}
void treat_packet(AVFrame *frame)
{
	
}

void close_decode(AVCodecContext *codec_ctx, AVFormatContext *fmt_ctx)
{
	avcodec_free_context(&codec_ctx);
	avformat_close_input(&fmt_ctx);
}

