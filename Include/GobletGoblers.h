#ifndef _GOBLET_GOBLERS_
#define _GOBLET_GOBLERS_

//SDL lib
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//Game engine
#include <board.h>

//Screen dimension constants
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
//Loaded media simultaniously in the window
#define MAX_LOADED_MEDIA 10
//declaration of a type ptr_func to void func
typedef void (*ptr_func)();

//main stuct which hold all necessary part of the SDL goblet_goblers
typedef struct
{
// main part of the struct
    // SDL based
    SDL_Window *game_window;
    SDL_Renderer *Renderer;
    SDL_Event evt;
    SDL_Surface *loadedSurface[MAX_LOADED_MEDIA]; // contain pointer to all loaded surfaces on screen
    // goblet_goblers component
    board game_board;

    // action on the struct
    ptr_func clear;
    ptr_func run;
    ptr_func quit;
} Game_Interface;

Game_Interface SetupGbtGblr();

#endif /*_GOBLET_GOBLERS_*/