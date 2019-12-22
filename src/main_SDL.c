#include <stdio.h>
#include <stdlib.h>
//graphical interface lib
#include <SDL2/SDL.h>
//game lib
#include <SDL_based_interface/GobletGoblers.h>

//gcc src/main_SDL.c -IC:\MinGW_lib\i686-w64-mingw32\include -IInclude -LC:\MinGW_lib\i686-w64-mingw32\lib -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o test
//gcc src/main_SDL.c -Iinclude -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o test
int main(int argc, char **argv)
{
    //The window we'll be rendering to
    SDL_Window *window = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    else
    {
        //Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            //SetupGbtGblr(window);
        }
    }
    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}