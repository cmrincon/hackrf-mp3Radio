#include "fifo.h"


uint8_t *buffer=NULL;
pthread_mutex_t lock;
pthread_cond_t write_cond;
pthread_cond_t read_cond;
volatile unsigned int read_dly;
volatile unsigned int write_dly;
volatile unsigned int free_bytes;

int init_fifo()
{
	buffer = malloc(BUFFERSIZE);
	if (buffer == NULL)
	{
		return (-1);
	}
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&write_cond, NULL);
	pthread_cond_init(&read_cond, NULL);
	read_dly = 0;
	write_dly = 0;
	free_bytes = BUFFERSIZE;
	return 0;
}
size_t fifo_pop(uint8_t *outdata,size_t len)
{
	unsigned int count_bytes=0;
	unsigned int available_bytes_till_end = 0;
	if (len == 0) return 0;

	pthread_mutex_lock(&lock);
	while ((BUFFERSIZE - free_bytes) <= 0)
	{
		pthread_cond_wait(&read_cond, &lock);
	}
	len = len > (BUFFERSIZE - free_bytes) ? (BUFFERSIZE - free_bytes) : len;
	
	if(write_dly > read_dly)
	{
		outdata = memcpy(outdata,(buffer + read_dly),len);
		read_dly += len;
		count_bytes = len;
	}
	else
	{
		available_bytes_till_end = BUFFERSIZE - read_dly;
		count_bytes = len > available_bytes_till_end ? available_bytes_till_end : len;
		outdata = memcpy(outdata, (buffer + read_dly), count_bytes);
		if (count_bytes == available_bytes_till_end)
		{
			memcpy(outdata + count_bytes, buffer, len - count_bytes);
			count_bytes = len;
		}
		read_dly = read_dly + len >= BUFFERSIZE ? read_dly+len - BUFFERSIZE : read_dly +len;
	}
	free_bytes += count_bytes;
	pthread_cond_signal(&write_cond);
	pthread_mutex_unlock(&lock);
	return count_bytes;
}
int fifo_push(const uint8_t *data, const size_t len)
{
	unsigned int start_bytes;
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
	
	if ((start_bytes = (BUFFERSIZE - write_dly)) < len)
	{
		memcpy((buffer + write_dly), data, start_bytes);
		memcpy(buffer, data + start_bytes, len - start_bytes);
		write_dly = len - start_bytes;
	}
	else
	{
		memcpy((buffer + write_dly), data, len);
		write_dly = (start_bytes == 0) ? 0 : write_dly + len ;
	}
	free_bytes -= len;
	pthread_cond_signal(&read_cond);
	pthread_mutex_unlock(&lock);
	return 0;
}
void free_fifo()
{
	free(buffer);
	pthread_cond_destroy(&write_cond);
	pthread_cond_destroy(&read_cond);
}









