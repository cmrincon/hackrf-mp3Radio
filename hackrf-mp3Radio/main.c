#include <stdlib.h>
#include "decode_mp3.h"
#include <pthread.h>

#define BUFFERSIZE 1<<13
void init_mutex(struct struc_mutex *mutex);
void destroy_mutex(struct struc_mutex *mutex);


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
	init_mutex(&threadArgs.mutex);
	
	
	//Program
	if (pthread_create(&thread_id, NULL, &decode, &threadArgs) != 0) exit(-1);
	if (pthread_join(thread_id, NULL) != 0) exit(-1);

	//close decoder

	free(threadArgs.outputbuffer);
	return 0;
}
void init_mutex(struct struc_mutex *mutex)
{
	//Add return value test
	pthread_mutex_init(&mutex->lock, NULL);
	pthread_cond_init(&mutex->cond_empty, NULL);
	pthread_cond_init(&mutex->cond_full, NULL);
}
void destroy_mutex(struct struc_mutex *mutex)
{
	pthread_cond_destroy(&mutex->cond_empty);
	pthread_cond_destroy(&mutex->cond_full);
}
