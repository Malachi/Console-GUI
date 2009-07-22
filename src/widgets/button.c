#include "button.h"
#include <stdio.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_ttf.h>

Button create_button( char* imf, char* imuf, Button* up, 
							Button* down, Button* left, 
							Button* right, SDL_Rect pos,
							buttonAction doAction, char* label)
{
	
	//if( strlen(imf) == 0 || strlen(imuf) == 0) return NULL;
	
	Button b;
	b.image_focused = imf;
	b.image_unfocused = imuf;
	b.up = up;
	b.down = down;
	b.left = left;
	b.right = right;
	b.position = pos;
	b.doAction = doAction;
	b.label = label;
	
	return b;
	
}


int draw_button(Button* btn, SDL_Surface * screen, int focused)
{
	
	SDL_Surface* btnimg = NULL;
	
	if(focused == 0) {
		btnimg = IMG_Load(btn->image_unfocused);
	}else{
		btnimg = IMG_Load(btn->image_focused);
	}
	
	if (btnimg == NULL) {
		return -1;
	}
	
	SDL_BlitSurface(btnimg, NULL, screen, &btn->position);
	
	
	/**
	 * Font
	 */
	if(btn->label!=NULL) {
		if(TTF_Init() == -1) {
			printf("TTF_Init: %s\n", TTF_GetError());
			exit(1);
		}
		
		TTF_Font *font;
		font=TTF_OpenFont("share/fonts/font.ttf", 20);
		if(!font) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}
		
		SDL_Color  color={255,255,255};
		SDL_Surface *label;
		if(!(label = TTF_RenderUTF8_Blended(font, btn->label, color))) {
			printf("Error drawing\n");
		}
		
		TTF_CloseFont(font); font=NULL;
		TTF_Quit();
		
		
		SDL_Rect lrect;
		lrect.x = btn->position.x + 70;
		lrect.y = btn->position.y + 20;
		
		SDL_BlitSurface(label, NULL, screen, &lrect);
		
		SDL_FreeSurface(label);
	}
	
	SDL_UpdateRect(screen,btn->position.x,btn->position.y,
					btnimg->w,btnimg->h);
	
	SDL_FreeSurface(btnimg);
	
	
		
	return 0;
		
}
