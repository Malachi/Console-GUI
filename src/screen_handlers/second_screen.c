#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>
#include "screen_handlers.h"
#include "second_screen.h"

// global variables

/**
 * This var is very important. It will hold the
 * return value. Which is either null or a pointer
 * to another screen handling function.
 */
pt2Func rh;

pt2Func second_screen_handler(SDL_Surface *screen)
{
	
	rh = NULL;
	
	SDL_Surface* bg =  IMG_Load("share/images/bg2.jpg");
	
	if (bg == NULL) {
		fprintf(stderr, "Couldn't load %s: %s\n", "bg2.png", SDL_GetError());
		exit(1);
	}
	
	SDL_Surface* tux =  IMG_Load("share/images/tux.png");
	
	if (tux == NULL) {
		fprintf(stderr, "Couldn't load %s: %s\n", "background.png", SDL_GetError());
		exit(1);
	}
	
	SDL_BlitSurface(bg, NULL, screen, NULL);
	
	SDL_BlitSurface(tux, NULL, screen, NULL);
	
	SDL_UpdateRect(screen,0,0,0,0);
	
	SDL_FreeSurface(bg);
	SDL_FreeSurface(tux);
	
	second_screen_event_listener(screen);
	
	return rh;
}





/**
 * Listen to events
 * 
 * Well, it's basically that, it listens to events and takes some action
 * depending on what happened.
 * A couple of things you should keep in mind when programming or 
 * modifying this kind of function is that a global variable rh is
 * provided. So if an action requires a change of screen, the only thing
 * you need to do is to assign a function pointer of another screen
 * handler to rh and then exit the event_listener.
 * 
 * @author Marcos Di Pietro
 */
void second_screen_event_listener(SDL_Surface* screen)
{
	
	SDL_Event event;	
	
	
	int done = 0;
	do
	{
		
		
		/**
		 * We wait for an event to happen and once it does, we try to
		 * distinguish between the different events that insterest us
		 * and take an action. If the event does not interest us then
		 * we just ignore the event.
		 */
		SDL_WaitEvent(&event);
		
		switch(event.type)
		{
			
								
				
					 
			case SDL_KEYUP:
				printf("%d\n",event.key.keysym.sym);
				switch(event.key.keysym.sym)
				{
					case 27:			// Escape key
						/**
						 * the escape key was pressed, so we make sure
						 * that rh is NULL and we return. Remember that
						 * a NULL pointer return value will result in
						 * the program exiting.
						 */
						rh = NULL;
						return;
						
						
					case 276:
						rh = (pt2Func)main_screen_handler;
						return;
						
				}
				break;
				
				
            case SDL_QUIT:
                exit(0);
		
		}
		
	}while(1==1);
	
}
