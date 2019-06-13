#include "fifo.h"


uint8_t *buffer=NULL;
pthread_mutex_t lock;
pthread_cond_t write_cond;
pthread_cond_t read_cond;
unsigned int read_dly;
unsigned int write_dly;
unsigned int free_bytes;

void init_fifo()
{
	buffer = malloc(BUFFERSIZE);
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&write_cond, NULL);
	pthread_cond_init(&read_cond, NULL);
	read_dly = 0;
	write_dly = 0;
	free_bytes = BUFFERSIZE;
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









