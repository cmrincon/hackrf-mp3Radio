#include <stdlib.h>


#define BUFFERSIZE 2^13

int main(void)
{
	
	char *frame_buffer = malloc(BUFFERSIZE);

	free(frame_buffer);
	return 0;
}