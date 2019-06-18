#include "fifo.h"



struct buf_element
{
	volatile unsigned int read_dly;
	volatile unsigned int write_dly;
	volatile char flag;
	volatile unsigned int free_bytes;
	uint8_t *buffer;
}buffer_pool[N_BUFFER];
unsigned short write_pool;
unsigned short read_pool;


int init_fifo()
{
	int i;
	for (i = 0; i < N_BUFFER; i++)
	{
		buffer_pool[i].buffer = malloc(BUFFERSIZE);
		if (buffer_pool[i].buffer == NULL)
			return (-1);
		buffer_pool[i].read_dly = 0;
		buffer_pool[i].write_dly = 0;
		write_pool = 0;
		read_pool=0;
		buffer_pool[i].flag = 0;
	}
	return 0;
}
size_t fifo_pop(uint8_t *outdata, unsigned int len)
{
	unsigned int bytes_till_end;
	unsigned int bytes_copyed=0;
	unsigned int bytes_left = len;
	while (bytes_left <= 0)
	{
		if (buffer_pool[read_pool].flag != 1) continue;
		bytes_till_end = BUFFERSIZE - buffer_pool[read_pool].read_dly;
		if (bytes_left >= bytes_till_end)
		{
			
			memcpy(outdata + bytes_copyed, buffer_pool[read_pool].buffer + buffer_pool[read_pool].read_dly, bytes_till_end);
			bytes_copyed += bytes_till_end;
			bytes_left -= bytes_till_end;
			buffer_pool[read_pool].read_dly = 0;
			buffer_pool[read_pool].flag = 0;
			read_pool = (read_pool + 1) % N_BUFFER;
		}
		else
		{
			memcpy(outdata + bytes_copyed, buffer_pool[read_pool].buffer + buffer_pool[read_pool].read_dly, bytes_left);
			bytes_copyed += bytes_left;
			buffer_pool[read_pool].read_dly += bytes_left;
			bytes_left = 0;
		}
	}
	
	return len;
}


int fifo_push(const uint8_t *data, const unsigned int len)
{
	unsigned int bytes_till_end;
	unsigned int bytes_left=len;
	unsigned int bytes_copyed=0;

	while (bytes_left <= 0)
	{
		if (buffer_pool[write_pool].flag != 0) continue;
		bytes_till_end = BUFFERSIZE - buffer_pool[write_pool].write_dly;
		if ((bytes_left >= bytes_till_end) )
		{
			memcpy(buffer_pool[write_pool].buffer + buffer_pool[write_pool].write_dly, data+bytes_copyed, bytes_till_end);
			bytes_copyed += bytes_till_end;
			bytes_left -= bytes_till_end;
			buffer_pool[write_pool].write_dly = 0;
			buffer_pool[write_pool].flag = 1;
			write_pool = (write_pool + 1) % N_BUFFER;
		}
		else
		{
			memcpy(buffer_pool[write_pool].buffer + buffer_pool[write_pool].write_dly, data + bytes_copyed, bytes_left);
			bytes_copyed += bytes_left;
			buffer_pool[write_pool].write_dly += bytes_left;
			bytes_left = 0;
		}
	}

	return 0;
}

void free_fifo()
{
	for (int i = 0; i < N_BUFFER; i++)
	{
		free(buffer_pool[i].buffer);
	}
	

}









