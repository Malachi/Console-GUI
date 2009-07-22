#include "video.h"


/**
 * Video initialization
 * 
 * This function is the one in charge of boostrapping the video 
 * rendering. Basically it initializes the video mode along with a 
 * couple of other settings and it then passes the execution handling
 * to some screen handler. For more detailed information see code.
 * 
 * A word on screen handlers
 * =========================
 * Well basically a screen handler is just a function. To make 
 * application more modular when it comes to screens, I decided that
 * each screen should be independent from the other one. To acomplish
 * this, I made use of function pointers. Basically what I'm doing is
 * setting a pointer to a function and calling the function given by
 * the pointer. Initially, it will call a predefined screen handler
 * (main_screen_handler, which is defined on 
 * `screen_handlers/main_screen.c`. This function will handle the
 * application execution until and event ocurrs in which it needs
 * either to exit the program or pass the handle to another screen
 * handler. 
 * 
 * HOW DO I SWITCH TO ANOTHER SCREEN HANDLER?
 * The screen handling functions return a screen handler. And when
 * called, the screen handlers are within a loop that will execute
 * until the screen handler returns a NULL pointer. Every time the
 * screen handler function returns execution control back to this 
 * function, this function will change the screen handling pointer and
 * call the new screen handler.
 * A little trick here that can be used is to return from within a 
 * screen handling function a pointer to itself. This way, the screen
 * will be refreshed and initialized to its initial state.
 * 
 * @author Marcos Di Pietro
 * 
 */
int video_initialize()
{

	// Initialize sdl video
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// What to do in case of failure
		fprintf(stderr, "Unable to initialize SDL");
		return 1;
	}
	
	
	// Schedule SDL_Quit to be run at exit
	atexit(SDL_Quit);
	
	
	// Set's the window's title, which won't be seen since its going
	// to be running on fullscreen mode
	SDL_WM_SetCaption("PLUG Gaming Console Frontend","PLUG Gaming Console Frontend");
	
	
	// Hide cursor
	SDL_ShowCursor(SDL_DISABLE);
	
	
	// Set the video mode
	screen = SDL_SetVideoMode(0,0,0, SDL_SWSURFACE | SDL_FULLSCREEN);
	
	
	
	
	/**
	 * Well this part is kind of tough to understand. Basically, a
	 * function pointer video_screen_handler, which is initialized to
	 * the main_screen_handler, will pass control of execution to the
	 * screen handler it points to. So, initially main_screen_handler
	 * will have the control of the application. If main_screen_handler
	 * wants to switch control to other handler, it will return a 
	 * function pointer of the handler that should take control. 
	 * video_screen_handler will take the value the current function
	 * it is pointing to returns.
	 * 
	 * video_screen_handler = (video_screen_handler)(1,2);
	 * 
	 * If a NULL pointer is returned by the screen handler, then the
	 * loop is terminated.
	 * 
	 */
	video_screen_handler = (pt2Func) main_screen_handler;
	do {
		
		video_screen_handler = (video_screen_handler)(screen);
		
	} while(video_screen_handler != NULL);
	
	
	
	return 0;
	
	
}
