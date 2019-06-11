#include <stdlib.h>
#include "decode_mp3.h"
#include <pthread.h>

#define BUFFERSIZE 1<<13

int main(int argc,char *argv[])
{
	pthread_t thread_id;
	struct decoder_args threadArgs;
	threadArgs.file_name=argv[1];
 
	if (argc != 2)
	{
		printf("Need only 1 argument: path of mp3 file\n");
		exit(-1);
	}
	
	//Init
	threadArgs.outputbuffer = malloc(BUFFERSIZE);
	
	
	//Program
	if (pthread_create(&thread_id, NULL, &decode, &threadArgs) != 0) exit(-1);
	if (pthread_join(thread_id, NULL) != 0) exit(-1);

	//close decoder

	free(threadArgs.outputbuffer);
	return 0;
}
