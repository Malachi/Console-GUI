#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>
#include "screen_handlers.h"
#include "audio.h"
#include "button.h"
#include "main_screen.h"
#include "media_center_screen.h"

// global variables

Button* currentButton = NULL;

/**
 * This var is very important. It will hold the
 * return value. Which is either null or a pointer
 * to another screen handling function.
 */
pt2Func rh;

/**
 * Well this is the main screen handler. This will take care rendering
 * images, event handling, and data flow of the main screen. I will
 * document it very very detailed so you can use this one as a template
 * to creating more screens.
 * 
 * @author Marcos Di Pietro
 */ 
pt2Func main_screen_handler(SDL_Surface *screen)
{
	
	/**
	 *  We initialize the return handler to NULL. So that if we return
	 * from the function, the application will exit. If we would like
	 * to change this behavior, we just have to change the value of rh
	 * and return. There's an example of this later on this file.
	 */
	rh = NULL;
	
	
	
	/**
	 * We load a couple of images... the background and the logo. If any
	 * of these fails, then we exit the program.
	 */
	SDL_Surface* bg = IMG_Load("share/images/background.png");
	
	if (bg == NULL) {
		fprintf(stderr, "Couldn't load %s: %s\n", "background.png", SDL_GetError());
		exit(2);
	}
	
	SDL_Surface* logo = IMG_Load("share/images/plug.png");
	
	if (bg == NULL) {
		fprintf(stderr, "Couldn't load %s: %s\n", "background.png", SDL_GetError());
		exit(1);
	}
	
	
	
	/**
	 * Once the images have been load, we will need to display them.
	 * Well that's what this code does.
	 */
	SDL_BlitSurface(bg, NULL, screen, NULL);
	SDL_BlitSurface(logo, NULL, screen, NULL);
	
	
	/**
	 * We modified the screen surface. So now we need to update the 
	 * screen or redraw it.
	 */
	SDL_UpdateRect(screen,0,0,0,0);
	
	
	/**
	 * Each time we create a new surface, we need to free them. 
	 * Otherwise, our application will be leaking memory and we don't
	 * want that to happen. Memory leaking is basically using memory
	 * without even knowing you are using it.
	 * SDL_FreeSurface(*surface) will free the surface for us.
	 */
	SDL_FreeSurface(bg);
	SDL_FreeSurface(logo);
	
	
	
	SDL_Rect btnrect;
	SDL_Rect btnrect2;
	
	Button btn;
	Button btn2;
	
	btnrect.x = 300;
	btnrect.y = 300;
	btn = create_button("share/images/button_template_focus.png", 
				"share/images/button_template.png", NULL, &btn2, NULL, NULL, 
				btnrect, (buttonAction) button1, "Media Center");
	draw_button(&btn, screen, 1);
	currentButton = &btn;
	
	
	
	btnrect2.x = 300;
	btnrect2.y = 400;
	btn2 = create_button("share/images/button_template_focus.png",
				"share/images/button_template.png", &btn, NULL, NULL, NULL, 
				btnrect2, (buttonAction) button2, "Exit");
	draw_button(&btn2, screen, 0);
	
	
	
	/**
	 * Now that we are done drawing to screen we pass the execution
	 * control to another function that will take care of listening
	 * and handling the events that happen in main screen.
	 */
	event_listener(screen);
	
	
	/**
	 * Once the event listener returns, we immediatly exit this function
	 * and return the value on rh. If rh has not been modified by 
	 * the event listener, then it will return a NULL pointer and the
	 * application will exit
	 */
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
void event_listener(SDL_Surface* screen)
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
			
				
			case SDL_MOUSEMOTION:
				//Handle Mouse Event
				break;
				
				
				
				
            case SDL_MOUSEBUTTONDOWN:
                printf("Mouse button %d pressed at (%d,%d)\n",
                       event.button.button, event.button.x, event.button.y);
				if(event.button.button == 2) return;
				if(event.button.button == 1) {
					
					/**
					 * VERY IMPORTANT
					 * Here is an example on how to switch to another 
					 * screen handler. We assign rh the function pointer
					 * that should be the next screen handler. Then,
					 * we just return.
					 * What will happen in this case is that 
					 * event_handler will return to main_screen_handler
					 * and main_screen_handler is going to trace back
					 * by returning a new function pointer to the 
					 * video_initialize function and the
					 * video_initialize function will then call the new
					 * screen handling function.
					 */
					rh = (pt2Func)media_center_screen_handler;//second_screen_handler;
					return;
				}
				break;
				
				
				
					 
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
						
											
					case 273:			// up arrow
						if(currentButton->up != NULL)
						{
							draw_button(currentButton, screen, 0);
							currentButton = currentButton->up;
							draw_button(currentButton, screen, 1);
						}
						break;
						
					case 274:			// down arrow
						if(currentButton->down != NULL)
						{
							draw_button(currentButton, screen, 0);
							currentButton = currentButton->down;
							draw_button(currentButton, screen, 1);
						}
						break;
						
					case 275:			// arrow right
						if(currentButton->right != NULL)
						{
							draw_button(currentButton, screen, 0);
							currentButton = currentButton->right;
							draw_button(currentButton, screen, 1);
						}
						break;
						
					case 276:			// arrow left
						if(currentButton->left != NULL)
						{
							draw_button(currentButton, screen, 0);
							currentButton = currentButton->left;
							draw_button(currentButton, screen, 1);
						}
						break;
						
						
					case 13:			// Enter key
						if( 1 == (currentButton->doAction)(currentButton, screen) ) return;
						break;
						
				}
				break;
				
				
            case SDL_QUIT:
                exit(0);
		
		}
		
	}while(1==1);
	
}





int button1(Button* myself, SDL_Surface* screen)
{
	rh = (pt2Func) media_center_screen_handler;
	return 1;
}


int button2(Button* myself, SDL_Surface* screen)
{
	exit(0);
}
