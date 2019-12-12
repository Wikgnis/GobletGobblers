#include "board.h"
#include <stdlib.h>

/**
 * \file board.c
 *
 * \brief Source code associated with \ref board.h
 *
 * \author LEBOCQ Titouan
 */

/**
 * @brief The board of the game, define it as you wish.
 */

typedef struct
{
	player player[3];
	size piece[3];
}case_s;

struct board_s {
	case_s board[3][3];
	size house[2][3];
};

board new_game(){ 
	// memory allocation for the board (leave it as is)
	board new_board = malloc(sizeof(struct board_s));
	for (int i = 0; i < 3; i++)
	{
		for (int e = 0; e < 3; e++)
		{
			for (int f = 0; f < 3; f++)
			{
				new_board->board[i][e].player[f] = NO_PLAYER;
				new_board->board[i][e].piece[f] = NONE;
			}
			
		}
		
	}
	
	for (int i = 0; i < 2; i++)
  {
    for (int e = 0; e < 3; e++)
    {
      new_board -> house[i][e] = 2;
    }
  }
  
	return new_board;
}

void destroy_game(board game){
	// freeing memory, necessary for memory allocated with malloc (leave as is)
	free(game);
}

board copy_game(board original_game){
	board copied_game = original_game;
	return copied_game;
}

player next_player(player current_player){
	player next_player;
	if (current_player != 1) next_player = 1;
	else next_player = 2;
	return next_player;
}