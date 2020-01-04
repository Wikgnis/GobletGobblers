#include <GobletGoblers.h>
// standart c lib
#include <stdio.h>
#include <stdlib.h>
//SDL related lib
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//Game engine
#include <board.h>

/*
gcc src/main_SDL.c lib/GobletGoblers.c lib/board.c -Iinclude -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o test
gcc src/main_SDL.c lib/GobletGoblers.c lib/board.c -Iinclude -Llib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o test
*/

//custom made circle creator algorythm for SDL
void SDL_RenderCircle(SDL_Renderer *renderer, int r, int xc, int yc)
{
    int x = 0, y = r;
    int d = 5 - 4*r;
    while (x<=y)
    {
        SDL_RenderDrawPoint(renderer, x + xc, y + yc);
        SDL_RenderDrawPoint(renderer, y + xc, x + yc);
        SDL_RenderDrawPoint(renderer, -x + xc, y + yc);
        SDL_RenderDrawPoint(renderer, -y + xc, x + yc);
        SDL_RenderDrawPoint(renderer, x + xc, -y + yc);
        SDL_RenderDrawPoint(renderer, y + xc, -x + yc);
        SDL_RenderDrawPoint(renderer, -x + xc, -y + yc);
        SDL_RenderDrawPoint(renderer, -y + xc, -x + yc);
        if (d>0){
            y--;
            d = d - 8*y;
        }
        x++;
        d = d+8*x+4;
    }
}

void SDL_RenderFillCircle(SDL_Renderer *renderer, int r, int xc, int yc)
{
    for (int i = 1; i <= r; i++)
    {
        SDL_RenderCircle(renderer, i, xc, yc);
    }
}

cursor newCursor()
{
    cursor initCurs = malloc(sizeof(struct _cursor));
    initCurs->coords[0] = 0;
    initCurs->coords[1] = 0;
    return initCurs;
}

void deleteCursor(cursor cursor)
{
    free(cursor);
    cursor = NULL;
}

void GobletGoblers_RenderCursor(Game_Interface *game)
{
    int scale = 10; // for thickness
    SDL_SetRenderDrawColor(game->Renderer, 0, 0, 0, 255);
    SDL_RenderSetScale(game->Renderer, scale, scale);
    SDL_Rect SDL_cursor = {
        ((game->board_info.coords[0]) + (game->cursor->coords[0]) * (game->board_info.size_case))/scale,
        ((game->board_info.coords[1]) + (game->cursor->coords[1]) * (game->board_info.size_case))/scale,
        game->board_info.size_case/scale,
        game->board_info.size_case/scale
    };
    SDL_RenderDrawRect(game->Renderer, &SDL_cursor);
    SDL_RenderSetScale(game->Renderer, 1, 1);
}

void GobletGoblers_RenderCase(Game_Interface *game, int line, int column)
{
    int onCase = get_place_holder(game->game_board, line, column);
    if ( onCase != 0)
    {
        int color[3];
        if (onCase == 1)
        {
            color[0] = 84;
            color[1] = 84;
            color[2] = 84;
        }
        else
        {
            color[0] = 242;
            color[1] = 235;
            color[2] = 211;
        }
        
        int x_case, y_case;
        x_case = game->board_info.coords[0] + column * game->board_info.size_case;
        y_case = game->board_info.coords[1] + line * game->board_info.size_case;
        SDL_SetRenderDrawColor(game->Renderer, color[0], color[1], color[2], 255);
        SDL_RenderFillCircle(
            game->Renderer,
            game->board_info.size_case / 7 * get_piece_size(game->game_board, line, column),
            x_case + game->board_info.size_case / 2,
            y_case + game->board_info.size_case / 2);
    }
}

void GobletGoblers_RenderBoard(Game_Interface *game)
{
    // board itself
    SDL_SetRenderDrawColor(game->Renderer, 20, 189, 172, 255);
    SDL_Rect SDL_board = {
        game->board_info.coords[0],
        game->board_info.coords[1],
        game->board_info.size,
        game->board_info.size
    };
    SDL_RenderFillRect(game->Renderer, &SDL_board);
    SDL_SetRenderDrawColor(game->Renderer, 13, 161, 146, 255);
    SDL_Rect line;
    int width = game->board_info.size / 50;
    for (int i = 1; i <= 2; i++)
    {
        //vert
        line.x = game->board_info.coords[0] + i * game->board_info.size_case - width / 2;
        line.y = game->board_info.coords[1];
        line.w = width;
        line.h = game->board_info.size;
        SDL_RenderFillRect(game->Renderer, &line);
        //hor
        line.x = game->board_info.coords[0];
        line.y = game->board_info.coords[1] + i * game->board_info.size_case - width / 2;
        line.w = game->board_info.size;
        line.h = width;
        SDL_RenderFillRect(game->Renderer, &line);
    }
    // pieces
    for (int i = 0; i < 3; i++)
    {
        for (int e = 0; e < 3; e++)
        {
            GobletGoblers_RenderCase(game, i, e);
        }
    }
    // cursor for selection
    GobletGoblers_RenderCursor(game);
}

void GobletGoblers_RunGame(Game_Interface *game)
{
    int quit = 0;
    while (!quit)
    {
        SDL_RenderClear(game->Renderer);
        GobletGoblers_RenderBoard(game);
        //event listener
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
                switch (game->evt.key.keysym.sym)
                {
                    case SDLK_UP:
                        game->cursor->coords[1]--;
                        if (game->cursor->coords[1] < 0)
                        {
                            game->cursor->coords[1] = 2;
                        }
                        break;

                    case SDLK_DOWN:
                        game->cursor->coords[1]++;
                        if (game->cursor->coords[1] > 2)
                        {
                            game->cursor->coords[1] = 0;
                        }
                        break;

                    case SDLK_LEFT:
                        game->cursor->coords[0]--;
                        if (game->cursor->coords[0] < 0)
                        {
                            game->cursor->coords[0] = 2;
                        }
                        break;

                    case SDLK_RIGHT:
                        game->cursor->coords[0] ++;
                        if (game->cursor->coords[0]>2)
                        {
                            game->cursor->coords[0] = 0;
                        }
                        break;

                    case SDLK_RETURN:
                        // enter choice mode
                        break;

                    default:
                        break;
                }
            }
        }
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

void freeMedia(Game_Interface *game)
{
    int i = 0;
    while (game->loadedSurface[i] != NULL)
    {
        printf("unload surface : %p\n", game->loadedSurface[i]);
        SDL_FreeSurface(game->loadedSurface[i]);
        game->loadedSurface[i] = NULL;
        i++;
    }
}

void GobletGoblers_QuitGame(Game_Interface *game)
{
    // unload all images
    freeMedia(game);
    //Quit TTF
    TTF_Quit();
    //Destroy renderer
    SDL_DestroyRenderer(game->Renderer);
    //Destroy window
    SDL_DestroyWindow(game->game_window);
    //Quit SDL subsystems
    SDL_Quit();
}

Game_Interface SetupGbtGblr()
{
    SDL_Window *game_window = NULL;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    //Initialise SDL TTF
    else if(TTF_Init() == -1)
    {
        printf("TTF init. failed - Error : %s\n", TTF_GetError());
    }
    else 
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
        // initialise the Game_Interface struct
            Game_Interface game;
            // SDL init
            game.game_window = game_window;
            game.Renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED);
            game.run = (*GobletGoblers_RunGame);
            game.quit = (*GobletGoblers_QuitGame);
            for (int i = 0; i < MAX_LOADED_MEDIA; i++)
            {
                game.loadedSurface[i] = NULL;
            }
            // Game engine init
            game.game_board = new_game();
            place_piece(game.game_board, 1, 1, 0, 0);
            place_piece(game.game_board, 2, 2, 1, 1);
            place_piece(game.game_board, 1, 3, 2, 2);
            // important gb gobblers values for SDL
            if (SCREEN_WIDTH * PERCENT_WIDTH_BOARD > SCREEN_HEIGHT)
            {
                game.board_info.size = SCREEN_HEIGHT;
                game.board_info.coords[0] = (SCREEN_WIDTH * PERCENT_WIDTH_BOARD - SCREEN_HEIGHT) / 2;
                game.board_info.coords[1] = 0;
            }
            else
            {
                game.board_info.size = SCREEN_WIDTH * PERCENT_WIDTH_BOARD;
                game.board_info.coords[0] = 0;
                game.board_info.coords[1] = (SCREEN_HEIGHT - SCREEN_WIDTH * PERCENT_WIDTH_BOARD) / 2;
            }
            game.board_info.size_case = game.board_info.size / 3;
            // cursor
            game.cursor = newCursor();
            return game;
        }
    }
}

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
/* without fill
        SDL_RenderDrawPoint(renderer, x + xc, y + yc);
        SDL_RenderDrawPoint(renderer, y + xc, x + yc);
        SDL_RenderDrawPoint(renderer, -x + xc, y + yc);
        SDL_RenderDrawPoint(renderer, -y + xc, x + yc);
        SDL_RenderDrawPoint(renderer, x + xc, -y + yc);
        SDL_RenderDrawPoint(renderer, y + xc, -x + yc);
        SDL_RenderDrawPoint(renderer, -x + xc, -y + yc);
        SDL_RenderDrawPoint(renderer, -y + xc, -x + yc);
        */
/* with fill
        SDL_RenderDrawLine(renderer, xc, yc, x + xc, y + yc);
        SDL_RenderDrawLine(renderer, xc, yc, y + xc, x + yc);
        SDL_RenderDrawLine(renderer, xc, yc, -x + xc, y + yc);
        SDL_RenderDrawLine(renderer, xc, yc, -y + xc, x + yc);
        SDL_RenderDrawLine(renderer, xc, yc, x + xc, -y + yc);
        SDL_RenderDrawLine(renderer, xc, yc, y + xc, -x + yc);
        SDL_RenderDrawLine(renderer, xc, yc, -x + xc, -y + yc);
        SDL_RenderDrawLine(renderer, xc, yc, -y + xc, -x + yc);
        */
/* test filled circle
void SDL_RenderFillCircle(SDL_Renderer *renderer, int r, int xc, int yc)
{
    for (int i = 1; i <= r; i++)
    {
        SDL_RenderCircle(renderer, i, xc, yc);
    }
}
void SDL_RenderFillCircle(SDL_Renderer *renderer, int r, int xc, int yc)
{
    int x = 0, y = r;
    int d = 5 - 4 * r;
    while (x <= y)
    {
        SDL_RenderDrawLine(renderer, xc, yc, x + xc, y + yc);
        SDL_RenderDrawLine(renderer, xc, yc, y + xc, x + yc);
        SDL_RenderDrawLine(renderer, xc, yc, -x + xc, y + yc);
        SDL_RenderDrawLine(renderer, xc, yc, -y + xc, x + yc);
        SDL_RenderDrawLine(renderer, xc, yc, x + xc, -y + yc);
        SDL_RenderDrawLine(renderer, xc, yc, y + xc, -x + yc);
        SDL_RenderDrawLine(renderer, xc, yc, -x + xc, -y + yc);
        SDL_RenderDrawLine(renderer, xc, yc, -y + xc, -x + yc);
        if (d > 0)
        {
            y--;
            d = d - 8 * y;
        }
        x++;
        d = d + 8 * x + 4;
    }
}
*/