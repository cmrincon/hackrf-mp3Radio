#include <portaudio.h>
#include <stdlib.h>

#define FRAMESPERBUFFER 2048

void init_audio();
void audio_write(const void* buffer, unsigned long n_frames);
void audio_close();
