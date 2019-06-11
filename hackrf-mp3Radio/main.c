#include <stdlib.h>
#include "decode_mp3.h"
#include <pthread.h>

#define BUFFERSIZE 2^13

int main(int argc,char *argv[])
{
	pthread_t thread_id;
	int ret;
	
	if (argc != 2)
	{
		printf("Need only 1 argument: path of mp3 file\n");
		exit(-1);
	}
	
	//Init
	frame_buffer = malloc(BUFFERSIZE);
	init_decode(argv[1]);
	
	
	//Program

	if (pthread_create(thread_id, NULL, decode, NULL) < 0) exit(-1);
	pthread_join(thread_id, &ret);

	//close decoder
	close_decode();
	free(frame_buffer);
	return 0;
}