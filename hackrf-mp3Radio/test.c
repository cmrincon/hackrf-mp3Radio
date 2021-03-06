#include "test.h"

void radioTest()
{
	initSDR(5e5,433.92e6,30);
	send();
	closeSDR();

}


void audioTest(const char filepath[])
{
	pthread_t thread_id;
	uint8_t buff[8192];
	unsigned int ndata;
	filo_ctx rawAudioBuffer;


	//Init
	if (filo_make(&rawAudioBuffer, BUFFERSIZE) != 0)
	{
		printf("Could not open FIFO buffer\n");
		goto close;
	}

	//Create the decoder thread
	if (pthread_create(&thread_id, NULL, &decode, filepath) != 0) exit(-1);

	sleep(2);
	// Play the buffer
	if ((ndata = filo_pop(&rawAudioBuffer, &buff[0], 1200)) > 0)
	{
		init_audio(format.nChannels, format.format, format.sampleRate);
		audio_write(&buff[0], ndata / format.n_bytes);
	}

	while ((ndata = filo_pop(&rawAudioBuffer, &buff[0], 1200)) > 0)
	{
		audio_write(&buff[0], ndata / format.n_bytes);
	}
	if (pthread_join(thread_id, NULL) != 0) goto close;
	//close decoder
close:
	filo_free(&rawAudioBuffer);
	audio_close();
}

