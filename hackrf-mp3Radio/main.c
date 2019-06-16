#include <stdlib.h>
#include "decode_mp3.h"
#include "fifo.h"
#include "audio.h"





int main(int argc,char *argv[])
{
	pthread_t thread_id;
	struct decoder_args threadArgs;
	uint8_t buff[8192];
	uint8_t buff_next[8192];
	int ndata;
	int ndata_next;

 
	if (argc != 2)
	{
		printf("Need only 1 argument: path of mp3 file\n");
		exit(-1);
	}
	threadArgs.file_name = argv[1];
	//Init
	init_fifo();
	init_audio();

	
	
	//Program
	if (pthread_create(&thread_id, NULL, &decode, &threadArgs) != 0) exit(-1);
	
	sleep(2);
	while ((ndata_next = fifo_pop(&buff_next[0], (size_t) 8192)) > 0)
	{
		audio_write(&buff[0], ndata);
		ndata = ndata_next;
		memcpy(&buff[0], &buff_next[0], ndata);
	}
	if (pthread_join(thread_id, NULL) != 0) exit(-1);
	//close decoder
	free_fifo();
	audio_close();
	return 0;
}
