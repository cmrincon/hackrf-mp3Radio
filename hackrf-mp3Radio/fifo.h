#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define BUFFERSIZE (unsigned int) (1<<16)

/**
* Init the buffers and the mutex.
* @return Returns 0 if there is no errors.
*/
int init_fifo();
/**
* Pop the contents to outdata. If there is not enought data in the buffer, the function will return 
* less bytes than requested.
* @param *outdata Pointer to the data.
* @param len Length of the data.
* @return Number of bytes copied to the buffer. 
*/
extern size_t fifo_pop(uint8_t *outdata, size_t len);
/**
* Push the contents of data to the buffer.
* @param data Pointer to the data.
* @param len Length of the data.
* @return Return 0 if there is no errors.
*/
extern int fifo_push(const uint8_t *data, const size_t len);

/**
* Free the resources of the buffer.
*/
void free_fifo();
extern unsigned int getFreeBytes();