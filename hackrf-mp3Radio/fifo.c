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
	pthread_mutex_lock(&lock);
	pthread_mutex_unlock(&lock);
}
int fifo_push(uint8_t *data, unsigned int len)
{
	long long start_bytes;
	if (len > BUFFERSIZE)
	{
		printf("Not enought buffer size\n");
		
		return (-1);
	}
	if (len < 0)
	{
		printf("data length < 1\n");
		return (-2);
	}
	pthread_mutex_lock(&lock);
	while (len > free_bytes)
	{
		pthread_cond_wait(&write_cond, &lock);
	}
	
	if ((start_bytes = BUFFERSIZE - write_dly) < len)
	{
		memcopy((buffer + write_dly), data, (BUFFERSIZE - write_dly));
		memcopy(buffer, data + start_bytes, len - start_bytes);
		write_dly = len - start_bytes;
	}
	else
	{
		memcopy((buffer + write_dly), data, len);
		write_dly = (start_bytes == 0) ? 0 : write_dly + len ;
	}
	free_bytes -= len;
	pthread_mutex_unlock(&lock);
	return 0;
}
void free_fifo()
{
	free(buffer);
	pthread_cond_destroy(&write_cond);
	pthread_cond_destroy(&read_cond);
}









