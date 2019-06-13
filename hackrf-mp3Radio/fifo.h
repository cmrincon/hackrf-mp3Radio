#include <stdint.h>
#include <pthread.h>

#define BUFFERSIZE 2<<15

void init_fifo();
extern int fifo_pop();
extern uint8_t fifo_push();
void free_fifo();
