#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "txtHandler.h"
#include "../board.h"

void save(board game, int save){
    char *str_save = NULL;
    char ch[1];
    str_save = malloc(sizeof(char[57]));
    str_save[0] = save + '0';
    str_save[1] = ' ';
    for (int i = 0; i<3; i++){
        for (int e = 0; e<3; e++){
            for (int f = 0; f < 3; f++){
                ch[0] = game->board[i][e].piece[f] + '0';
                strcat(str_save, ch);
                ch[0] = game->board[i][e].player[f] + '0';
                strcat(str_save, ch);
            }
        }
    }
    replace_line("Goblet_Gobblers_saves.txt", save, str_save);
    free(str_save);
}

void loadSaves(char *filename, int save, board game){
    char *copySave;
    int test;
    copySave = malloc(sizeof(char[70]));
    save = save * 19 + 1;

    readFile(filename, copySave);
    int rang = 2;

    for (int i = 0; i < 3; i++)
    {
        for (int e = 0; e < 3; e++)
        {
            for (int f = 0; f < 3; f++)
            {
                test = copySave[rang] - '0';
                game->board[i][e].piece[f] = test;
                test = copySave[rang + 1] - '0';
                game->board[i][e].player[f] = test;
                rang += 2;
            }
            
        }
    }
    free(copySave);
    printInfoBoard(game);
}