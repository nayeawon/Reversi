#include <ncurses.h>

void display(int board[8][8])
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printw("+---");
        }
        printw("+\n");
        
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == -1)
                printw("|   ");
            else if (board[i][j] == 0)
                printw("| 0 ") ;
            else
                printw("| O ") ;
        }
        printw("|\n");
    }
    
    for (int j = 0; j < 8; j++) {
        printw("+---");
    }
    printw("+\n");
}