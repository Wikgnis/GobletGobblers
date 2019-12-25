#ifndef _GOBLET_GOBLERS_
#define _GOBLET_GOBLERS_

#include <SDL2/SDL.h>
#include <board.h>

typedef void (*ptr_func)();

typedef struct
{
    SDL_Window *game_window;
    SDL_Event evt;
    SDL_Renderer *Renderer;

    ptr_func run;
} Game_Interface;

//Screen dimension constants
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

Game_Interface SetupGbtGblr(SDL_Window *game_window);

#endif /*_GOBLET_GOBLERS_*/