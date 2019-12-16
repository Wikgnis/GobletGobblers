#include <stdio.h>
#include <stdlib.h>
#include "txtHandler.h"
#include "../board.h"

void save(board game, int save){
    char *str_save = NULL;
    str_save = malloc(sizeof(char[19]));
    str_save[0] = 't';
    int rang = 1;
    for (int i = 0; i<3; i++){
        for (int e = 0; e < 3; e++){
            str_save[rang] = get_piece_size(game, i, e)+48;
            str_save[rang+1] = get_place_holder(game, i, e)+48;
            rang+=2;
            printf("%d\n%s\n", getSizeStr(str_save), str_save);
        }
    }
    replace_line("Goblet_Gobblers_saves.txt", save, str_save);
    free(str_save);
}