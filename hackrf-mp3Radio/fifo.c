#include "fifo.h"


#define BUFFERSIZE 2<<13
uint8_t *buffer;
pthread_mutex_t lock;
pthread_cond_t write_cond;
pthread_cond_t read_cond;

void init_fifo()
{
	buffer = malloc(BUFFERSIZE);
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&write_cond, NULL);
	pthread_cond_init(&read_cond, NULL);

}
int fifo_pop()
{

	return 0;
}
uint8_t fifo_push()
{

}
void free_fifo()
{
	free(buffer);
	pthread_cond_destroy(&write_cond);
	pthread_cond_destroy(&read_cond);
}









