#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFERSIZE (unsigned int) (2<<15)

int init_fifo();
extern size_t fifo_pop(uint8_t *outdata, size_t len);
extern int fifo_push(const uint8_t *data, const size_t len);
void free_fifo();