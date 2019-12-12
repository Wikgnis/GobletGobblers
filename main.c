#include "terminal.h"
#include "board.h"
#include "input.h"
#include <stdio.h>
#include <unistd.h>

// largeur 70

/*
    DONE _ Deplacement pion
    DONE _ empecher lancement choix pion si sur pion
    DONE _ surligner type pion => mode selection
    DONE _ Afficher nb pion in house
    DONE _ Message quand quitte mode jeu
    DONE _ annuler placement pion
    DONE _ pb quand entrée puis fleche
    Affichage pion possibles
    Affichage mode selection
    Affichage settings
    proper affichage error
    proper affichage choice with choice possible
    affichage end game

    Regles
    fonction detection arrow key + enter

    Save :
        auto on game ( ask resume when come back)
        and manual

    Bot :
        facile
        normal
        difficile

    Structure pour passage de flags
    DONE _ Refonte affichage general
    switch case in place of if else
    detection coup possible
    compartimentation fonction
    In setting enable/disable place player piece on player piece
    Portabilité
*/

size getMaxSize(board game, player player)
{
    size max = 0;
    for (int i = 1; i < 4; i++)
    {
        if (get_nb_piece_in_house(game, player, i) != 0) max = i;
    }
    return max;
}

int IsPossible(board game, player player, int line, int row)
{
    int flag = 0;
    if (getMaxSize(game, player) > get_piece_size(game, line, row)) flag = 1;
    return flag;
}

void printStart(int choice)
{
    home();
    positionCursor(18, 2);
    printInterminal(" ▄▄ •       ▄▄▄▄· ▄▄▌  ▄▄▄ .▄▄▄▄▄", red);
    positionCursor(18, 3);
    printInterminal("▐█ ▀ ▪▪     ▐█ ▀█▪██•  ▀▄.▀·•██  ", red);
    positionCursor(18, 4);
    printInterminal("▄█ ▀█▄ ▄█▀▄ ▐█▀▀█▄██▪  ▐▀▀▪▄ ▐█.▪", red);
    positionCursor(18, 5);
    printInterminal("▐█▄▪▐█▐█▌.▐▌██▄▪▐█▐█▌▐▌▐█▄▄▌ ▐█▌·", red);
    positionCursor(18, 6);
    printInterminal("·▀▀▀▀  ▀█▄▀▪·▀▀▀▀ .▀▀▀  ▀▀▀  ▀▀▀ ", red);
    positionCursor(20, 7);
    printInterminal(" ▄▄ •       ▄▄▄▄· ▄▄▌  ▄▄▄ .▄▄▄  .▄▄ · ", red);
    positionCursor(20, 8);
    printInterminal("▐█ ▀ ▪▪     ▐█ ▀█▪██•  ▀▄.▀·▀▄ █·▐█ ▀. ", red);
    positionCursor(20, 9);
    printInterminal("▄█ ▀█▄ ▄█▀▄ ▐█▀▀█▄██▪  ▐▀▀▪▄▐▀▀▄ ▄▀▀▀█▄ by", red);
    positionCursor(20, 10);
    printInterminal("▐█▄▪▐█▐█▌.▐▌██▄▪▐█▐█▌▐▌▐█▄▄▌▐█•█▌▐█▄▪▐█ LEBOCQ", red);
    positionCursor(20, 11);
    printInterminal("·▀▀▀▀  ▀█▄▀▪·▀▀▀▀ .▀▀▀  ▀▀▀ .▀  ▀ ▀▀▀▀ Titouan", red);
    positionCursor(28,13);
    if (choice == 0)
    {
        setAttr(whiteBg);
        printInterminal("startserdcftygv", red);
        setAttr(blackBg);
        printInterminal(" | quit", white);
        printInterminal(" | Settings", white);
     }
     if (choice == 1)
     {
         printInterminal("start | ", white);
         setAttr(whiteBg);
         printInterminal("quit", red);
         setAttr(blackBg);
         printInterminal(" | Settings", white);
     }
     if (choice == 2)
     {
         
         printInterminal("start | ", white);
         printInterminal("quit | ", white);
         setAttr(whiteBg);
         printInterminal("settings", red);
         setAttr(blackBg);
     }
}

void printLoadTXT(int choice, int x, int y)
{
    char printArray[5] = {
        ' ',
        ' ',
        ' ',
        ' ',
        ' '
    };
    printArray[choice] = '>';
    positionCursor(x, y);
    printf("%c New Game %c  \n", printArray[0], printArray[0] == '>'? printArray[0]-2: printArray[0]);
    positionCursor(x, y+1);
    printf("%c Save 1 (not fonctionnal)%c  \n", printArray[1], printArray[1] == '>'? printArray[1]-2: printArray[1]);
    positionCursor(x, y+2);
    printf("%c Save 2 (not fonctionnal)%c  \n", printArray[2], printArray[2] == '>'? printArray[2]-2: printArray[2]);
    positionCursor(x, y+3);
    printf("%c Save 3 (not fonctionnal)%c  \n", printArray[3], printArray[3] == '>'? printArray[3]-2: printArray[3]);
    positionCursor(x, y+4);
    printf("%c To menu %c  \n", printArray[4], printArray[4] == '>'? printArray[4]-2: printArray[4]);
}

void printLoad(int choice)
{
    home();
    positionCursor(9, 2);
    printInterminal("    _   _  ___  _   _ _ __   ___  __ ___   _____  ___ ", red);
    positionCursor(9, 3);
    printInterminal("   | | | |/ _ \\| | | | '__| / __|/ _` \\ \\ / / _ \\/ __|", red);
    positionCursor(9, 4);
    printInterminal("   | |_| | (_) | |_| | |    \\__ \\ (_| |\\ V /  __/\\__ \\", red);
    positionCursor(9, 5);
    printInterminal("    \\__, |\\___/ \\__,_|_|    |___/\\__,_| \\_/ \\___||___/", red);
    positionCursor(9, 6);
    printInterminal("     __/ |                                            ", red);
    positionCursor(9, 7);
    printInterminal("    |___/                                             ", red);

    positionCursor(3, 9);
    setAttr(redBg);
    for (int i = 0; i < 70; i++)
        printf(" ");
    setAttr(blackBg);
    printLoadTXT(choice, 30, 11);
}

char *colorPlayer(player player)
{
    char *color;
    if (player == 1)
        color = blue1;
    else if (player == 2)
        color = purple;
    return color;
}

void printBoard(board game, player current, int lineNumber, int rowNumber, int sourceLine, int sourceRow, int mode)
{
    int row = 0, column = 0;
    char *couleur_joueur, color;
    player onCase;
    size pieceSize;

    couleur_joueur = colorPlayer(current);

    home();
    positionCursor(17, 3);
    printInterminal("Au tour du ", red);
    printInterminal("joueur ", couleur_joueur);
    printf("%s%s%d%s%s", esc, couleur_joueur, current, esc, white);

    for (int i = 1; i <= 2; i++)
    {
        couleur_joueur = colorPlayer(i);
        positionCursor(39, 6+i);
        printf("%s%sjoueur %d:%s%s  ", esc, couleur_joueur, i, esc, white);
        for (int j = 1; j < 4; j++)
        {
            for (int e = 0; e < get_nb_piece_in_house(game, i, j); e++)
            {
                if (j == 1) printf("%s%so%s%s", esc, couleur_joueur, esc, white);
                if (j == 2) printf("%s%sO%s%s", esc, couleur_joueur, esc, white);
                if (j == 3) printf("%s%s0%s%s", esc, couleur_joueur, esc, white);
            }
            printf(" | ");
        }
        
        printf("\n");
    }

    couleur_joueur = colorPlayer(current);
    positionCursor(20, 5);
    printInterminal("+---+---+---+", white);
    for (int i = 0; i < DIMENSIONS; i++)
    {
        positionCursor(20, 6 + 2*i);
        for (int j=0; j<DIMENSIONS; j++)
        {
            printf("| ");
            onCase = get_place_holder(game, i, j);
            if (sourceLine == i && sourceRow == j && mode == 2) setAttr(whiteBg);
            else if (lineNumber == i && rowNumber == j) setAttr(whiteBg);
            if (onCase != 0)
            {
                if (onCase == 1)
                    couleur_joueur = blue1;
                else if (onCase == 2)
                    couleur_joueur = purple;
                pieceSize = get_piece_size(game, i, j);
                if (pieceSize == 1)
                    printInterminal("o", couleur_joueur);
                if (pieceSize == 2)
                    printInterminal("O", couleur_joueur);
                if (pieceSize == 3)
                    printInterminal("0", couleur_joueur);
                    printInterminal("", white);
            }
            else printf(" ");
            setAttr(blackBg);
            printf(" ");
        }
        printf("|");
        positionCursor(20, 7 + 2 * i);
        printf("+---+---+---+");
    }
    positionCursor(25, 13);
    if (lineNumber == 3)
    {
        
        setAttr(whiteBg);
        printf("Exit");
        setAttr(blackBg);
    }
    else
    {
        printf("Exit");
    }
}

void moveOnBoard(board game, int *lineNumber, int *rowNumber, int *mode, int *exitGame)
{
    int choosing = 1, action=0;
    char ch;
    while (choosing)
    {
        initTermios();
        switch (fgetc(stdin))
        {
        case 27:
            if (fgetc(stdin) == 91)
            {

                switch (fgetc(stdin))
                {

                case 65:
                    (*lineNumber)--; //up
                    break;
                case 66:
                    (*lineNumber)++; //down
                    break;
                case 67:
                    (*rowNumber)++; //right
                    break;
                case 68:
                    (*rowNumber)--; //left
                    break;

                default:
                    break;
                }

                if ((*rowNumber) > 2)
                    (*rowNumber) = 0;
                else if ((*rowNumber) < 0)
                    (*rowNumber) = 2;
                else if ((*lineNumber) > 3)
                    (*lineNumber) = 0;
                else if ((*lineNumber) < 0)
                    (*lineNumber) = 2;

                choosing = 0;
            }
            break;
        case 10:
            if ((*lineNumber) == 3)
                (*exitGame) = 1;
            else if ((*mode) == 0)
            {
                (*mode) = 1;
            }
            else if ((*mode) == 2)
            {
                (*mode) = 3;
            }
            choosing = 0;
            break;

        default:
            break;
        }
        resetTermios();
    }
}

void startGame()
{
    board game=new_game();
    player current = 1;

    int sizePion = 0,
        lineNumber = 0,
        rowNumber = 0,
        sourceLine,
        sourceRow,
        mode = 0,
        exitGame=0,
        choosing = 1,
        choice = 0;
    char ch;

    clear();

    while (get_winner(game) == 0 && !exitGame)
    {
        printBoard(game, current, lineNumber, rowNumber, sourceLine, sourceRow, mode);
        moveOnBoard(game, &lineNumber, &rowNumber, &mode, &exitGame);
        if (mode == 1) //selection
        {
            if (get_place_holder(game, lineNumber, rowNumber) == NONE
                || IsPossible(game, current, lineNumber, rowNumber))
                {
                    positionCursor(39, 9);
                    printf("0 : cancel | 1 : small | 2 : medium | 3 : large | enter : move piece");
                    while (choosing)
                    {
                        initTermios();

                        switch (fgetc(stdin))
                        {
                        case '0':
                            sizePion = 0;
                            choosing = 0;
                            break;
                        case '1':
                            sizePion = 1;
                            choosing = 0;
                            break;
                        case '2':
                            sizePion = 2;
                            choosing = 0;
                            break;
                        case '3':
                            sizePion = 3;
                            choosing = 0;
                            break;
                        case 10:
                            if (get_place_holder(game, lineNumber, rowNumber) == current)
                            {
                                mode = 2;
                                sourceLine = lineNumber;
                                sourceRow = rowNumber;
                                choosing = 0;
                                positionCursor(39, 5);
                                printf("Selection mode");
                            }
                            sizePion = 0;

                        default:
                            break;
                        }

                        resetTermios();
                    }
                    choosing = 1;
                    if (!place_piece(game, current, sizePion, lineNumber, rowNumber))
                        current = next_player(current);
                    clear();
                    if (mode != 2)
                        mode = 0;
                }
        }
        else if (mode == 3) // Move mode
        {
            if (!move_piece(game, sourceLine, sourceRow, lineNumber, rowNumber)
            && (sourceLine != lineNumber && sourceRow != rowNumber))
            {
                current = next_player(current);
            }
            mode = 0;
        }
    if (exitGame){
        clear();
        while (choosing)
        {
            printf("Are you sure?\n");
            if (choice == 0)
            {
                printf("> Yes <\n No   \n");
            }
            else if (choice == 1){
                printf(" Yes   \n> No <\n");
            }
            initTermios();
            switch (fgetc(stdin))
            {
            case 27:
                if (fgetc(stdin) == 91)
                {
                    switch (fgetc(stdin))
                    {

                    case 65:
                        choice--; //up
                        break;
                    case 66:
                        choice++; //down
                        break;

                    default:
                        break;
                    }

                    if (choice > 1) choice = 0;
                    else if (choice < 0) choice = 1;
                }
                    break;

            case 10:
                if (choice == 1) exitGame = 0;
                choice = 0;
                choosing = 0;
                break;

            default:
                break;
            }
            resetTermios();
            clear();
        }
        choosing = 1;
         if (exitGame)
         {
             while (choosing)
             {
                 printf("Want to save? (not fonctionnal yet)\n");
                 if (choice == 0)
                 {
                     printf("> Yes <\n No   \n");
                 }
                 else if (choice == 1)
                 {
                     printf(" Yes   \n> No <\n");
                 }
                 initTermios();
                 switch (fgetc(stdin))
                 {
                 case 27:
                     if (fgetc(stdin) == 91)
                     {
                         switch (fgetc(stdin))
                         {

                         case 65:
                             choice--; //up
                             break;
                         case 66:
                             choice++; //down
                             break;

                         default:
                             break;
                         }

                         if (choice > 1)
                             choice = 0;
                         else if (choice < 0)
                             choice = 1;
                     }
                     break;

                 case 10:
                     if (choice == 0) // save
                    {
                        printf(" ");
                    }
                    choosing = 0;
                     break;

                 default:
                     break;
                 }
                 resetTermios();
                 clear();
                 destroy_game(game);
             }
             choosing = 1;
         }
    }
    }
    clear();
}

void printSettings(int choice)
{
    home();
    positionCursor(15, 1);
    printInterminal("   _____      _   _   _                 ", red);
    positionCursor(15, 2);
    printInterminal("  / ____|    | | | | (_)                ", red);
    positionCursor(15, 3);
    printInterminal(" | (___   ___| |_| |_ _ _ __   __ _ ___ ", red);
    positionCursor(15, 4);
    printInterminal("  \\___ \\ / _ \\ __| __| | '_ \\ / _` / __|", red);
    positionCursor(15, 5);
    printInterminal("  ____) |  __/ |_| |_| | | | | (_| \\__ \\", red);
    positionCursor(15, 6);
    printInterminal(" |_____/ \\___|\\__|\\__|_|_| |_|\\__, |___/", red);
    positionCursor(15, 7);
    printInterminal("                               __/ |    ", red);
    positionCursor(15, 8);
    printInterminal("                              |___/     ", red);
    positionCursor(0, 10);
    setAttr(redBg);
    for (int i = 0; i < 70; i++)
    {
        printf(" ");
    }
    setAttr(blackBg);
    positionCursor(35, 12);

}

int main()
{
    int menu=0,
        choice=0,
        choiceSave=0,
        running=1,
        choosing = 1,
        save[3];

    char ch;

    clear();
    cursorControl(cursorDown, 1);
    while (running==1)
    {
        if (menu==0) // start menu
        {
            printStart(choice);
            while (choosing)
            {
                initTermios();
                ch = fgetc(stdin);
                if (ch==27)
                {
                    ch = fgetc(stdin);
                    if (ch == 91){
                        ch = fgetc(stdin);
                        if (ch == 68)
                        {
                            choice--;
                        }
                        else if (ch == 67)
                        {
                            choice++;
                        }
                        if (choice<0) choice = 2;
                        if (choice>2) choice = 0;
                        choosing = 0;
                    }
                }
                if (ch == 10)
                {
                    if (choice == 1) 
                    {
                        running = 0;
                    }
                    else if (choice == 0) 
                    {
                        choice = 0;
                        menu = 1;
                    }
                    else if (choice == 2)
                    {
                        choice = 0;
                        menu = 2;
                    }
                    clear();
                    choosing = 0;
                }
                resetTermios();
            }
            choosing = 1;
        }
        else if (menu==1) // load
        {
            printLoad(choice);
            while (choosing)
            {
                initTermios();
                ch = fgetc(stdin);
                if (ch == 27)
                {
                    ch = fgetc(stdin);
                    if (ch == 91)
                    {
                        ch = fgetc(stdin);
                        if (ch == 65)
                        {
                            choice--;
                        }
                        else if (ch == 66)
                        {
                            choice++;
                        }
                        if (choice < 0)
                            choice = 4;
                        if (choice > 4)
                            choice = 0;
                        choosing = 0;
                    }
                }
                if (ch == 10)
                {
                    if (choice == 4)
                    {
                        menu = 0;
                        choice = 0;
                    }
                    else if (choice == 0)
                    {
                        menu = 3;
                        choice = 0;
                    }
                    clear();
                    choosing = 0;
                }
                resetTermios();
            }
            choosing = 1;
        }
        else if (menu==3) // game
        {
            startGame();
            menu = 1;
        }
        else if (menu == 2) // settings
        {
            printSettings(choice);
            /*
            while (choosing)
            {
                initTermios();
                switch (fgetc(stdin))
                {
                case 27:
                    if (fgetc(stdin) == 91)
                    {

                        switch (fgetc(stdin))
                        {

                        case 65:
                            (*lineNumber)--; //up
                            break;
                        case 66:
                            (*lineNumber)++; //down
                            break;
                        case 67:
                            (*rowNumber)++; //right
                            break;
                        case 68:
                            (*rowNumber)--; //left
                            break;

                        default:
                            break;
                        }

                        

                        choosing = 0;
                    }
                    break;
                case 10:
                    
                    choosing = 0;
                    break;

                default:
                    break;
                }
                resetTermios();
            }
            choosing = 1;
        }
        */
        }
    }
    return 0;
}