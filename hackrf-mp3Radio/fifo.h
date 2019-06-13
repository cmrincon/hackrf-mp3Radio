#include <stdint.h>
#include <pthread.h>

#define BUFFERSIZE 2<<15

void init_fifo();
extern uint8_t fifo_pop();
extern int fifo_push(const uint8_t *data, const size_t len);
void free_fifo();
