/**
* Implementation of first input last output queue.
*/

#pragma once
#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define BUFFERSIZE (unsigned int) (1<<16)

typedef struct filo_ctx_t
{
	uint8_t *buffer;
	pthread_mutex_t lock;
	pthread_cond_t write_cond;
	pthread_cond_t read_cond;
	volatile unsigned int read_dly;
	volatile unsigned int write_dly;
	volatile unsigned int free_bytes;
	unsigned int bufferLength;
}filo_ctx;

/**
* Init the buffers and the mutex.
* @return Returns 0 if there is no errors.
*/
int filo_make(filo_ctx *pipe, size_t size);
/**
* Pop the contents to outdata. If there is not enought data in the buffer, the function will return 
* less bytes than requested.
* @param *outdata Pointer to the data.
* @param len Length of the data.
* @return Number of bytes copied to the buffer. 
*/
size_t filo_pop(filo_ctx *pipe, uint8_t *outputData, size_t length);
/**
* Push the contents of data to the buffer.
* @param data Pointer to the data.
* @param len Length of the data.
* @return Return 0 if there is no errors.
*/
int filo_push(filo_ctx *pipe, const uint8_t *inputData, const size_t length);
/**
* Free the resources of the buffer.
*/
void filo_free(filo_ctx *pipe);
extern unsigned int getFreeBytes(filo_ctx *pipe);