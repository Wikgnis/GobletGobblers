// http://ascii-table.com/ansi-escape-sequences-vt-100.php
#define esc "\033"
// colors
#define blue "[0;94m"
#define blue1 "[1;94m"
#define blue2 "[1;36m"
#define green "[1;32m"
#define red "[1;31m"
#define purple "[1;35m"
#define black "[1;30m"
#define red "[1;31m"
#define cyan "[1;36m"
#define brown "[0;33m"
#define yellow "[1;33m"
#define white "[1;37m"
// foreground
#define blackFg "30"
#define redFg "31"
#define greenFg "32"
#define yellowFg "33"
#define blueFg "34"
#define magentaFg "35"
#define cyanFg "36"
#define whiteFg "37"
// background
#define blackBg "40"
#define redBg "41"
#define greenBg "42"
#define yellowBg "43"
#define blueBg "44"
#define magentaBg "45"
#define cyanBg "46"
#define whiteBg "47"
// formatting
#define lineWrap "[7h"
#define noLineWrap "[7l"
//cursor control
#define cursorHome "[H"
#define cursorUp "[A"
#define cursorDown "[B"
#define cursorForward "[C"
#define cursorBackward "[D"
// erase text
#define eraseToEndLine "[k"
#define eraseToStartLine "[1k"
#define eraseLine "[2k"
#define eraseDown "[J"
#define eraseUp "[1J"
#define eraseScreen "[2J"

/**
 * @brief clear the terminal
 */
void clear();

/**
 * @brief print in terminal
 * @param string string you want to print
 * @param color color of the printing in terminal
 */
void printInterminal(char string[], char color[]);

/**
 * @brief go to start of terminal if you have text on the first line it will be erased
 */
void home();

/**
 * @brief It's only for presentation: go back to the top of the terminal
 */
void exitTerminal();

/**
 * @brief set attributs of terminal
 * @param attr string which correspond to an attribut
 */
void setAttr(char attr[]);

/**
 * @brief control the position of the cursor
 * @param control string which correspond to an attribut
 * @param execution number of execution of the fonction
 */
void cursorControl(char control[], int execution);

/**
 * @brief control the position of the cursor
 * @param mode string which define the erasing mode
 */
void erase(char mode[]);

/**
 * @brief position the cursor on the x/y axis
 * @param x value on the x axis
 * @param y value on the y axis
 */
void positionCursor(int x, int y);