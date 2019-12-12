#include <termios.h>
#include <stdio.h>
 
static struct termios old, new;

void initTermios()
{
  tcgetattr(0, &old);
  new = old;
  new.c_lflag &= ~ICANON;
  new.c_lflag &= 0 ? ECHO : ~ECHO;
  tcsetattr(0, TCSANOW, &new);
}
 

void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}