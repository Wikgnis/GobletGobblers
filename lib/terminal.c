#include <stdio.h>
#include <TxtBasedInterface/terminal.h>


// pour deplacement curseur "\033[x,yf" (start at 1)
void clear()
{
    home();
    printf("%s[2J", esc);
}

void hide_cursor(){
    printf("\e[?25l");
}

void show_cursor(){
    printf("\e[?25h");
}

void printInterminal(char string[], char color[])
{
    printf("%s%s%s%s%s", esc, color, string, esc, white);
}

void erase(char mode[])
{
    printf("%s%s", esc, mode);
}

void home()
{
    printf("%s[H", esc);
}

void setAttr(char attr[])
{
    printf("%s[%sm", esc, attr);
}

void cursorControl(char control[], int execution)
{
    for (int i=0; i<execution; i++)
    {
        printf("%s%s ", esc, control);
    }
}

void exitTerminal()
{
    printf("%s[H", esc);
}

void positionCursor(int x, int y)
{
    printf("%s[%d;%dH", esc, y, x);
}