#ifndef __GUI_AUDIO

#include <SDL.h>
#include <SDL_audio.h>

#define NUM_SOUNDS 2
struct sample {
    Uint8 *data;
    Uint32 dpos;
    Uint32 dlen;
} sounds[NUM_SOUNDS];

int audio_initialize(char *file);
void audio_close();
void audio_mute();
void audio_unmute();
void PlaySound(char *file);

void mixaudio(void *unused, Uint8 *stream, int len);
SDL_AudioSpec fmt;

#define __GUI_AUDIO
#endif
