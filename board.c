#include "board.h"
#include <stdlib.h>
#include <stdio.h>

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
	return current_player != 1 ? 1 : 2;
}

player get_place_holder(board game, int line, int column){
	player onCase = NO_PLAYER;
	for (int i = 2; i >= 0 && onCase == NO_PLAYER; i--)
	{
		if (game->board[line][column].player[i] != NO_PLAYER){
			onCase = game->board[line][column].player[i];
		}
	}
	return onCase;
}

size get_piece_size(board game, int line, int column){
	size piece_size = NONE;
	for (int i = 2; i >= 0 && piece_size == NONE; i--)
	{
		if (game->board[line][column].piece[i] != NONE)
		{
			piece_size = game->board[line][column].piece[i];
		}
	}
	return piece_size;
}

player get_winner(board game){
	return 0;
};

int get_nb_piece_in_house(board game, player checked_player, size piece_size){
	int nb_piece = 0;
	if ((checked_player == PLAYER_1 || checked_player == PLAYER_2) && (piece_size >= SMALL && piece_size <= LARGE))
	{
		nb_piece = game->house[checked_player-1][piece_size-1];
		printf("test");
	}
	return nb_piece;
};

int place_piece(board game, player current_player, size piece_size, int line, int column);

int move_piece(board game, int source_line, int source_column, int target_line, int target_column);

void printInfoBoard(board game){
	printf("Houses :\n");
	for (int i = 0; i < 2; i++)
	{
		for (int e = 0; e < 3; e++)
		{
			printf("house[%d] | %d : %d\n", i + 1, e + 1, game->house[i][e]);
		}
		printf("\n");
	}
	printf("Board :\n");
	for (int i = 0; i < 3; i++)
	{
		for (int e = 0; e < 3; e++)
		{
			printf("case [%d %d] :\n", i, e);
			for (int f = 0; f < 3; f++)
			{
				printf("level %d :\n", f);
				printf("\tplayer : %d\n", game->board[i][e].player[f]);
				printf("\tpiece : %d\n", game->board[i][e].piece[f]);
			}
		}
		printf("\n");
	}
}

int main(void){
	board game = new_game();
	printInfoBoard(game);
	return 0;
}