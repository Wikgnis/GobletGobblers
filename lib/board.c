#include <stdlib.h>
#include <stdio.h>
#include <board.h>
/**
 * \file board.c
 *
 * \brief Source code associated with \ref board.h
 *
 * \author LEBOCQ Titouan
 */

board new_game()
{
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
			new_board->house[i][e] = 2;
		}
	}

	return new_board;
}

void destroy_game(board game)
{
	// freeing memory, necessary for memory allocated with malloc (leave as is)
	free(game);
}

board copy_game(board original_game)
{
	board copied_game = malloc(sizeof(struct board_s));
	copied_game = original_game;
	return copied_game;
}

player next_player(player current_player)
{
	return current_player != 1 ? 1 : 2;
}

player get_place_holder(board game, int line, int column)
{
	player onCase = NO_PLAYER;
	for (int i = 2; i >= 0 && onCase == NO_PLAYER; i--)
	{
		if (game->board[line][column].player[i] != NO_PLAYER)
		{
			onCase = game->board[line][column].player[i];
		}
	}
	return onCase;
}

size get_piece_size(board game, int line, int column)
{
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

player test_line(board game, int line)
{
	player player_onCase = get_place_holder(game, line, 0);
	int nb_in_line = 1;
	for (int i = 1; i < 3 && player_onCase; i++)
	{
		if (get_place_holder(game, line, i) == player_onCase)
		{
			nb_in_line += 1;
		}
	}
	return (nb_in_line == 3) ? player_onCase : NO_PLAYER;
}

player test_column(board game, int column)
{
	player player_onCase = get_place_holder(game, 0, column);
	int nb_in_line = 1;
	for (int i = 1; i < 3 && player_onCase; i++)
	{
		if (get_place_holder(game, i, column) == player_onCase)
		{
			nb_in_line += 1;
		}
	}
	return (nb_in_line == 3) ? player_onCase : NO_PLAYER;
}

player test_diag1(board game)
{
	player player_onCase = get_place_holder(game, 0, 0);
	int nb_in_line = 1;
	for (int i = 1; i < 3 && player_onCase; i++)
	{
		if (get_place_holder(game, i, i) == player_onCase)
		{
			nb_in_line += 1;
		}
	}
	return (nb_in_line == 3) ? player_onCase : NO_PLAYER;
}

player test_diag2(board game)
{
	player player_onCase = get_place_holder(game, 2, 0);
	int nb_in_line = 1;
	for (int i = 1; i < 3 && player_onCase; i++)
	{
		if (get_place_holder(game, 2 - i, i) == player_onCase)
		{
			nb_in_line += 1;
		}
	}
	return (nb_in_line == 3) ? player_onCase : NO_PLAYER;
}

player get_winner(board game)
{
	player winner = NO_PLAYER, temp;
	int different_win = 0;
	for (int i = 0; i < 3 && !different_win; i++)
	{
		temp = test_column(game, i);
		if (temp != NO_PLAYER)
		{
			if (temp == winner || winner == NO_PLAYER)
			{
				winner = temp;
			}
			else if (temp != winner)
			{
				different_win++;
			}
		}
		temp = test_line(game, i);
		if (temp != NO_PLAYER)
		{
			if (temp == winner || winner == NO_PLAYER)
			{
				winner = temp;
			}
			else if (temp != winner)
			{
				different_win++;
			}
		}
	}
	temp = test_diag1(game);
	if (temp != NO_PLAYER)
	{
		if (temp == winner || winner == NO_PLAYER)
		{
			winner = temp;
		}
		else if (temp != winner)
		{
			different_win++;
		}
	}
	temp = test_diag2(game);
	if (temp != NO_PLAYER)
	{
		if (temp == winner || winner == NO_PLAYER)
		{
			winner = temp;
		}
		else if (temp != winner)
		{
			different_win++;
		}
	}

	return !different_win ? winner : NO_PLAYER;
};

int get_nb_piece_in_house(board game, player checked_player, size piece_size)
{
	int nb_piece = 0;
	if ((checked_player == PLAYER_1 || checked_player == PLAYER_2) && (piece_size >= SMALL && piece_size <= LARGE))
	{
		nb_piece = game->house[checked_player - 1][piece_size - 1];
	}
	return nb_piece;
};
/*
stands for (source): the piece is not available in the player's house.
stands for (target): the piece is to small to be put there.
stands for illegal entries: e.g. a too large line number.
Otherwise, returns a (standard) 0 for success.
*/
int place_piece(board game, player current_player, size piece_size, int line, int column)
{
	int return_state;
	if // correct entry
		(
			(piece_size >= SMALL && piece_size <= LARGE)				  // correct piece size
			&& (current_player == PLAYER_1 || current_player == PLAYER_2) // correct player
			&& ((line >= 0 && line <= 2) && column >= 0 && column <= 2)   // correct line and column
		)
	{
		if (get_piece_size(game, line, column) < piece_size)
		{
			if (get_nb_piece_in_house(game, current_player, piece_size) > 0)
			{
				game->board[line][column].piece[piece_size - 1] = piece_size;
				game->board[line][column].player[piece_size - 1] = current_player;
				game->house[current_player - 1][piece_size - 1]--;
				return_state = 0;
			}
			else
				return_state = 1;
		}
		else
			return_state = 2;
	}
	else
		return_state = 3;
	return return_state;
}
/*
stands for (source): there is no piece at the initial place.
stands for (target): the piece is too small to be put at the target place.
stands for illegal entries: e.g. a too large line number.
Otherwise, returns a (standard) 0 for success.
*/
int move_piece(board game, int source_line, int source_column, int target_line, int target_column)
{
	size piece_size = get_piece_size(game, source_line, source_column);
	player player_onCAse = get_place_holder(game, source_line, source_column);
	int return_state;
	if (
		(target_line >= 0 && target_line <= 2 && target_column >= 0 && target_column <= 2) && (source_line >= 0 && source_line <= 2 && source_column >= 0 && source_column <= 2))
	{
		if (piece_size != NONE)
		{
			if (!place_piece(game, player_onCAse, piece_size, target_line, target_column))
			{
				game->board[source_line][source_column].piece[piece_size - 1] = NONE;
				game->board[source_line][source_column].player[piece_size - 1] = NO_PLAYER;
				game->house[player_onCAse - 1][piece_size - 1]++;
				return_state = 0;
			}
			else
				return_state = 2;
		}
		else
			return_state = 1;
	}
	else
		return_state = 3;
	return return_state;
}

void printInfoBoard(board game)
{
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