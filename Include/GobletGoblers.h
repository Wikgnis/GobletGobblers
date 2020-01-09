#ifndef _GOBLET_GOBLERS_
#define _GOBLET_GOBLERS_

//SDL lib
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//Game engine
#include <board.h>

//Screen dimension constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 950
//Loaded media simultaniously in the window
#define MAX_LOADED_MEDIA 10

// different status of the widow
typedef enum {NOTHING_LOADED, WINDOW_LOADED, BOARD_LOADED, WINDOW_UPDATE} status;

//enum for loaded media
enum board_media
{
    CURRENT_PLAYER,
    HOUSE_1_SMALL,
    HOUSE_1_MEDIUM,
    HOUSE_1_LARGE,
    HOUSE_2_SMALL,
    HOUSE_2_MEDIUM,
    HOUSE_2_LARGE
};

//declaration of a type ptr_func to void func
typedef void (*ptr_func)();

// gb gobblers board info for sdl
typedef struct{
    int coords[2];
    int size;
    int size_case;
}_SDL_Board_Info;

//
typedef struct {
    SDL_Surface *surface[MAX_LOADED_MEDIA];
    SDL_Texture *texture[MAX_LOADED_MEDIA];
} _loaded_media;

// cursor used to play
enum _cursor_type {CHOICE = 0, PLACE, MOVE};
typedef enum _cursor_type cursor_type;
struct _cursor
{
    int coords[2];
    int source_coords[2];
    cursor_type type;
};
typedef struct _cursor *cursor;

//main stuct which hold all necessary part of the SDL goblet_goblers
typedef struct
{
// main part of the struct
    // SDL based
    SDL_Window *game_window;
    SDL_Renderer *Renderer;
    SDL_Event evt;
    _loaded_media loaded_media;
    status current_status;
    // graphic interface
    _SDL_Board_Info board_info;
    // goblet_goblers component
    board game_board;
    cursor cursor;
    player current_player;
    // action on the struct
    ptr_func run;
    ptr_func quit;
} Game_Interface;

Game_Interface SetupGbtGblr();

#endif /*_GOBLET_GOBLERS_*/