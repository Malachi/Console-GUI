#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "screen_handlers.h"
#include "media_center_screen.h"
#include "error_codes.h"

extern pt2Func rh;

/**
 * Screen Handler entry function for the Media Center screen 
 * @param screen the surface that this screen uses
 * @author Alwyn Malachi Berkeley Jr.
 */
pt2Func media_center_screen_handler(SDL_Surface* screen)
{
	// set the background
	const char* mediaCenterBG = "share/images/thinkopen_wide.png";
	SDL_Surface* mediaSurfaceBG = media_center_set_background(mediaCenterBG);

	// draw the active components
	media_center_render(screen, mediaSurfaceBG);
	
	// clean up
	media_center_clean_up(mediaSurfaceBG);

	// listen for events
	media_center_listen_events(screen);

	return rh;
}

/**
 * Listens for events on in the window.
 * @param screen the primary sdl surface
 * @author Alwyn Malachi Berkeley Jr.
 */
void media_center_listen_events(SDL_Surface* screen) {
	SDL_Event event;

	while (1) {
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						rh = NULL;
						return;
					case SDLK_BACKSPACE:
						rh = (pt2Func)main_screen_handler;
						return;
					default:
						break;
				}
				break;
			case SDL_QUIT:
				exit(0);
			default:
				break;
		}
	}
}

/**
 * Sets an image into the window background.
 * @param backgroundImage the filename of an image including path
 * @return a pointer to a SDL_Surface containing the image
 * @author Alwyn Malachi Berkeley Jr.
 */
SDL_Surface* media_center_set_background(const char* backgroundImage) {
	SDL_Surface* background = IMG_Load(backgroundImage);
	
	if (background == NULL) {
		fprintf(stderr, "Couldn't load %s: %s\n", backgroundImage, SDL_GetError());
		exit(MC_BG_LOAD_ERROR);
	}

	return background;
}

/**
 * Renders all active/set objects.
 * @param screen the primary SDL_Surface
 * @param background surface containing the background image
 * @author Alwyn Malachi Berkeley Jr.
 */
void media_center_render(SDL_Surface* screen, SDL_Surface* background) {
	SDL_BlitSurface(background, NULL, screen, NULL);

	SDL_Flip(screen);
}

/**
 * Cleans up memory referenced for the scene.
 * @author Alwyn Malachi Berkeley Jr.
 */
void media_center_clean_up(SDL_Surface* s1) {
	SDL_FreeSurface(s1);
}
