#include <stdint.h>
#include <pthread.h>

void init_fifo();
int fifo_pop();
uint8_t fifo_push();
void free_fifo();
