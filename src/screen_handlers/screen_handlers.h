#include <SDL.h>

typedef void*(*pt2Func)(SDL_Surface *screen);

pt2Func main_screen_handler(SDL_Surface *screen);
pt2Func second_screen_handler(SDL_Surface *screen);
