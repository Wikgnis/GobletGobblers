#include <GobletGoblers.h>
#include <stdio.h>
#include <SDL2/SDL.h>

// gcc src/main_SDL.c lib/GobletGoblers.c  -Iinclude -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o test

/*
SDL_WINDOW_FULLSCREEN fullscreen window
SDL_WINDOW_FULLSCREEN_DESKTOP fullscreen window at the current desktop resolution
SDL_WINDOW_OPENGL window usable with OpenGL context
SDL_WINDOW_VULKAN window usable with a Vulkan instance
SDL_WINDOW_SHOWN
SDL_WINDOW_HIDDEN window is not visible
SDL_WINDOW_BORDERLESS no window decoration
SDL_WINDOW_RESIZABLE window can be resized
SDL_WINDOW_MINIMIZED window is minimized
SDL_WINDOW_MAXIMIZED window is maximized
SDL_WINDOW_INPUT_GRABBED window has grabbed input focus
SDL_WINDOW_ALLOW_HIGHDPI window should be created in high-DPI mode if supported (>= SDL 2.0.1)
*/

//https://lazyfoo.net/tutorials/SDL/08_geometry_rendering/index.php

//SDL_SetRenderDrawColor color out and in
//SDL_RenderDrawPoint point
//render circles : Bresenham circle algorithm

/*
    SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_RenderFillRect( gRenderer, &fillRect );
*/

/*
    //Update screen
    SDL_RenderPresent(gRenderer);
*/

// https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/

void SDL_RenderCircle(){
    
}

    void
    run(Game_Interface *game)
{
    int quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&(game->evt)) != 0)
        {
            //User requests quit
            if (game->evt.type == SDL_QUIT)
            {
                quit = 1;
            }
            //User presses a key
            else if (game->evt.type == SDL_KEYDOWN)
            {
                //Select surfaces based on key press
                switch (game->evt.key.keysym.sym)
                {
                    case SDLK_UP:
                        break;

                    case SDLK_DOWN:
                        break;

                    case SDLK_LEFT:
                        break;

                    case SDLK_RIGHT:
                        break;

                    default:
                        break;
                }
            }
        }
        
        //Clear screen
        SDL_SetRenderDrawColor(game->Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(game->Renderer);
        //Render red filled quad
        SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_SetRenderDrawColor(game->Renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(game->Renderer, &fillRect);
        //Update screen
        SDL_RenderPresent(game->Renderer);
    }
}

/*
    //Key press surfaces constants
    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };
*/

Game_Interface SetupGbtGblr(SDL_Window *game_window)
{
    //Create window
    game_window = SDL_CreateWindow("Goblet Goblers",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (game_window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        Game_Interface game;
        game.game_window = game_window;
        game.Renderer = SDL_CreateRenderer(game.game_window, -1, SDL_RENDERER_ACCELERATED);
        game.run = (*run);
        return game;
    }
}