#ifndef __GUI_VIDEO

#include <SDL.h>
#include "screen_handlers/screen_handlers.h"

SDL_Surface* screen;
int video_loop;

pt2Func video_screen_handler;


int video_initialize();


#define __GUI_VIDEO
#endif
