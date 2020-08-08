#include "decode_mp3.h"


char* frame_buffer;

int init_decode(char* file_name, AVCodecContext **codec_ctx, AVFormatContext **fmt_ctx, int *stream_index)
{
	AVCodec *codec;
	int a;
	av_register_all();
	if ((*fmt_ctx = avformat_alloc_context()) == NULL) return (-1);
	a = avformat_open_input(fmt_ctx, file_name, NULL, NULL);
	if ( a < 0)
	{
		printf("Error: %d", a);
		return (-1);
	}
	if  (avformat_find_stream_info(*fmt_ctx, NULL) < 0) 
		return (-1);
	*stream_index = av_find_best_stream(*fmt_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	if ((codec = avcodec_find_decoder(AV_CODEC_ID_MP3)) == NULL) 
		return (-1);
	*codec_ctx = avcodec_alloc_context3(codec);
	if (avcodec_open2(*codec_ctx,codec,NULL) < 0) 
		return (-1);
	return 0;
}


void* decode(decoder_args args)
{
	int ret = -1, stream_idx=0, decod_return;
	AVCodecContext *codec_ctx = NULL;
	AVFormatContext *fmt_ctx = NULL;
	AVPacket packet;
	AVFrame *frame;
	char *filename = (char *) args.file_name;
	void (*treatment)(filo_ctx*, AVFrame*) = NULL;
	   

	//INIT DECODE
	av_init_packet(&packet);
	if ((frame = av_frame_alloc()) == NULL) pthread_exit(&ret);
	if (init_decode(filename, &codec_ctx, &fmt_ctx, &stream_idx) < 0)
	{
		close_decode(codec_ctx, fmt_ctx);
		pthread_exit(&ret);
	}
	char first_time = 1;
	//START THE DECODING!
	do
	{
		decod_return = av_read_frame(fmt_ctx, &packet);
		if (decod_return < 0) break;
		if (packet.stream_index == stream_idx)
		{
			if (avcodec_send_packet(codec_ctx, &packet) < 0)
			{
				printf("ERROR\n");
				//exit(-1);
			}
			if (avcodec_receive_frame(codec_ctx, frame) != 0)
			{
				printf("ERROR\n");
				//exit(-1);
			}
			if (first_time)
			{
				treatment = getFormat(frame);
				if (treatment == 0)
				{
					printf("Format not supported\n");
					exit(-1);
				}
				first_time = 0;
			}
			treatment(args.outputBuffer, frame);
			av_frame_unref(frame);
		}
	} while (1); //need a exit condition.
	av_frame_free(&frame);
	close_decode(codec_ctx, fmt_ctx);
	ret = 0;
	return NULL;
}
void treat_packet(AVFrame *frame)
{
	
}

void close_decode(AVCodecContext *codec_ctx, AVFormatContext *fmt_ctx)
{
	avcodec_free_context(&codec_ctx);
	avformat_close_input(&fmt_ctx);
}

