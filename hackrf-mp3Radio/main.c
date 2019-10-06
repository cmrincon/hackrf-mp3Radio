#include <stdlib.h>
#include "decode_mp3.h"
#include "fifo.h"
#include "audio.h"



int main(int argc,char *argv[])
{
	pthread_t thread_id;
	struct decoder_args threadArgs;
	uint8_t buff[8192];
	unsigned int ndata;

 
	if (argc != 2)
	{
		printf("Need only 1 argument: path of mp3 file\n");
		exit(-1);
	}
	threadArgs.file_name = argv[1];
	//Init
	if (init_fifo() != 0)
	{
		printf("Could not open FIFO buffer\n");
		goto close;
	}
	init_audio();

	
	
	//Program
	if (pthread_create(&thread_id, NULL, &decode, &threadArgs) != 0) exit(-1);
	
	sleep(2);
	while ((ndata = fifo_pop(&buff[0],  1200)) > 0)
	{
		audio_write(&buff[0], ndata);
	}
	if (pthread_join(thread_id, NULL) != 0) goto close;
	//close decoder
	close:
	free_fifo();
	audio_close();
	return 0;
}
