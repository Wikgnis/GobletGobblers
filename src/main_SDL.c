#include <stdio.h>
#include <stdlib.h>
//game lib
#include <GobletGoblers.h>
//graphical interface lib
#include <SDL2/SDL.h>

// gcc src/main_SDL.c lib/GobletGoblers.c  -Iinclude -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o test

int main(int argc, char **argv)
{
    //The window we'll be rendering to
    SDL_Window *window = NULL;
    Game_Interface game;

        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    else
    {
        game = SetupGbtGblr(window);
        game.run(&game);
    }

    //Destroy window
    SDL_DestroyWindow(window);
    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}