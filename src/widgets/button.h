#include <SDL.h>

typedef int(*buttonAction)(void* myself, SDL_Surface* screen);

typedef struct __BUTTON{
	char* image_focused;
	char* image_unfocused;
	
	struct __BUTTON *up;
	struct __BUTTON *down;
	struct __BUTTON *left;
	struct __BUTTON *right;
	
	SDL_Rect position;
	
	buttonAction doAction;
	
	char *label;
	 
} Button;

Button create_button( char* imf, char* imuf, Button* up, 
							Button* down, Button* left, 
							Button* right, SDL_Rect pos,
							buttonAction doAction, char* label);


int draw_button( Button* btn, SDL_Surface * screen, int focused);
