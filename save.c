#include <stdio.h>
#include <stdlib.h>
#include "board.h"

int save(board game, char typeSave)
{
    int state = 0, i = 0;
    char fileTXT[50]; // value change needed
    FILE* fichierSave = NULL;
    fichierSave = fopen("save.txt", "r");
    if (fichierSave != NULL)
    {
        while (fgets(fileTXT, 50, fichierSave) != NULL)
        {
            i++;
            printf("%s", fileTXT);
        }
        fclose(fichierSave);
    } else state = 1;
    return state;
}

int main()
{
    board game;
    save(game, 'd');
}