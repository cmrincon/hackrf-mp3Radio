#include "audio.h"


PaStreamParameters outputParameters;
PaStream *stream;

void init_audio()
{
	
	Pa_Initialize();
	outputParameters.device = Pa_GetDefaultOutputDevice();
	outputParameters.channelCount = 2;
	outputParameters.sampleFormat = paInt16;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	Pa_OpenStream(	& stream,  NULL,  & outputParameters, 48000, FRAMESPERBUFFER, paClipOff,  NULL, NULL);
	Pa_StartStream(stream);

}
void audio_write(const void* buffer, unsigned long n_bytes)
{
	Pa_WriteStream(stream,buffer,n_bytes/4);
}
void audio_close()	
{
	Pa_CloseStream(stream);
	Pa_Terminate();

}
