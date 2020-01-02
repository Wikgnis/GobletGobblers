#ifndef _GOBLET_GOBLERS_
#define _GOBLET_GOBLERS_


#include <SDL2/SDL.h>
#include <board.h>
#include <SDL2/SDL_ttf.h>

typedef void (*ptr_func)();

typedef struct
{
    SDL_Window *game_window;
    SDL_Event evt;
    SDL_Renderer *Renderer;

    ptr_func run;
    ptr_func quit;
} Game_Interface;

//Screen dimension constants
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900

Game_Interface SetupGbtGblr();

#endif /*_GOBLET_GOBLERS_*/