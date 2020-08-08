#include "fifo.h"


int filo_make(filo_ctx *pipe, size_t size)
{
	pipe->buffer = malloc(size);
	if (pipe->buffer == NULL)
	{
		return (-1);
	}
	pthread_mutex_init(&pipe->lock, NULL);
	pthread_cond_init(&pipe->write_cond, NULL);
	pthread_cond_init(&pipe->read_cond, NULL);
	pipe->read_dly = 0;
	pipe->write_dly = 0;
	pipe->free_bytes = size;
	pipe->bufferLength = size;
	return 0;
}
size_t filo_pop(filo_ctx *pipe, uint8_t *outputData, size_t length)
{
	unsigned int count_bytes = 0;
	unsigned int available_bytes_till_end = 0;
	if (length == 0) return 0;

	pthread_mutex_lock(&pipe->lock);
	while ((pipe->bufferLength - pipe->free_bytes) <= 0) 
	{
		pthread_cond_wait(&pipe->read_cond, &pipe->lock);
	}
	length = length > (pipe->bufferLength - pipe->free_bytes) ? (pipe->bufferLength - pipe->free_bytes) : length;

	if (pipe->write_dly > pipe->read_dly)
	{
		memcpy(outputData, (pipe->buffer + pipe->read_dly), length);
		pipe->read_dly += length;
		count_bytes = length;
	}
	else
	{
		available_bytes_till_end = pipe->bufferLength - pipe->read_dly;
		count_bytes = length > available_bytes_till_end ? available_bytes_till_end : length;
		memcpy(outputData, (pipe->buffer + pipe->read_dly), count_bytes);
		if (count_bytes == available_bytes_till_end)
		{
			memcpy(outputData + count_bytes, pipe->buffer, length - count_bytes);
			count_bytes = length;
		}
		pipe->read_dly = pipe->read_dly + length >= pipe->bufferLength ?
			pipe->read_dly + length - pipe->bufferLength : pipe->read_dly + length;
	}
	pipe->free_bytes += count_bytes;
	pthread_cond_signal(&pipe->write_cond);
	pthread_mutex_unlock(&pipe->lock);
	return count_bytes;
}
int filo_push(filo_ctx *pipe, const uint8_t *inputData, const size_t length)
{
	unsigned int start_bytes;
	if (length > pipe->bufferLength)
	{
		printf("Not enought buffer size\n");
		return (-1);
	}
	if (length < 0)
	{
		printf("data length < 1\n");
		return (-2);
	}
	pthread_mutex_lock(&pipe->lock);
	while (length > pipe->free_bytes)
	{
		pthread_cond_wait(&pipe->write_cond, &pipe->lock);
	}

	if ((start_bytes = (pipe->bufferLength - pipe->write_dly)) < length)
	{
		memcpy((pipe->buffer + pipe->write_dly), inputData, start_bytes);
		memcpy(pipe->buffer, inputData + start_bytes, length - start_bytes);
		pipe->write_dly = length - start_bytes;
	}
	else
	{
		memcpy((pipe->buffer + pipe->write_dly), inputData, length);
		pipe->write_dly = (start_bytes == 0) ? 0 : pipe->write_dly + length;
	}
	pipe->free_bytes -= length;
	pthread_cond_signal(&pipe->read_cond);
	pthread_mutex_unlock(&pipe->lock);
	return 0;
}
void filo_free(filo_ctx *pipe)
{
	free(pipe->buffer);
	pthread_cond_destroy(&pipe->write_cond);
	pthread_cond_destroy(&pipe->read_cond);
}
unsigned int getFreeBytes(filo_ctx *pipe)
{
	pthread_mutex_lock(&pipe->lock);
	unsigned int result = pipe->free_bytes;
	pthread_mutex_unlock(&pipe->lock);
	return result;
}








