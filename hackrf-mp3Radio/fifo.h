#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	

#define BUFFERSIZE (unsigned int) (2<<8)
#define N_BUFFER 10
int init_fifo();
extern size_t fifo_pop(uint8_t *outdata, unsigned int len);
extern int fifo_push(const uint8_t *data, const unsigned int len);
void free_fifo();
