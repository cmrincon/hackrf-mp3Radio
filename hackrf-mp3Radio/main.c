#include <stdlib.h>
#include "decode_mp3.h"
#include "fifo.h"





int main(int argc,char *argv[])
{
	pthread_t thread_id;
	struct decoder_args threadArgs;
 
	if (argc != 2)
	{
		printf("Need only 1 argument: path of mp3 file\n");
		exit(-1);
	}
	threadArgs.file_name = argv[1];
	//Init
	init_fifo();
	
	
	//Program
	if (pthread_create(&thread_id, NULL, &decode, &threadArgs) != 0) exit(-1);
	if (pthread_join(thread_id, NULL) != 0) exit(-1);

	//close decoder
	free_fifo();
	return 0;
}
