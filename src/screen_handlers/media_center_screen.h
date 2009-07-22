#include <SDL.h>

pt2Func media_center_screen_handler(SDL_Surface* screen);
void media_center_listen_events(SDL_Surface* screen);
SDL_Surface* media_center_set_background(const char* backgroundImage);
void media_center_render(SDL_Surface* screen, SDL_Surface* background);
void media_center_clean_up(SDL_Surface* s1);
