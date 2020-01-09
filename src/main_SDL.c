// standart c lib
#include <stdio.h>
//game lib
#include <GobletGoblers.h>

int main(int argc, char **argv)
{
    Game_Interface game;
    game = SetupGbtGblr();
    game.run();
    game.quit(&game);
    printf("End of the program.");

    return 0;
}