#include <SDL2/SDL.h>
#include <GameEngine/board.h>
#include <stdio.h>
#include <stdlib.h>

//gcc src/main_SDL.c -IC:\MinGW_lib\i686-w64-mingw32\include -IInclude -LC:\MinGW_lib\i686-w64-mingw32\lib -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o test
int main(int argc, char **argv)
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return -1;
    }



    /* Quit SDL */
    SDL_Quit();

    return 0;
}