#include "audio.h"


PaStreamParameters outputParameters;
PaStream *stream;

void init_audio(unsigned int channels, enum eFormat format, unsigned int sampleRate)
{
	
	Pa_Initialize();
	outputParameters.device = Pa_GetDefaultOutputDevice();
	outputParameters.channelCount = channels;

	if (format == pafloat32)
		outputParameters.sampleFormat = paFloat32;
	else if (format == paint16)
		outputParameters.sampleFormat = paInt16;
	else if (format == paint32)
		outputParameters.sampleFormat = paInt32;
	else if (format == paint24)
		outputParameters.sampleFormat = paInt24;
	else if (format == pauint8)
		outputParameters.sampleFormat = paUInt8;
	else if (format == paint8)
		outputParameters.sampleFormat = paInt8;

	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	Pa_OpenStream(	& stream,  NULL,  & outputParameters, sampleRate, FRAMESPERBUFFER, paClipOff,  NULL, NULL);
	Pa_StartStream(stream);

}
void audio_write(const void* buffer, unsigned int n_frames)
{
	Pa_WriteStream(stream,buffer, n_frames);
}
void audio_close()	
{
	Pa_CloseStream(stream);
	Pa_Terminate();

}
