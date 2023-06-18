#include <ncurses.h>
#include "game.h"

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

int next_move(Coordinate * pos[64])
{
    // Enable attributes for blinking text
    attron(A_BLINK);

    for (int i = 0 ; i < 64 ; i++) {
        if (pos[i] == NULL)
            break ;
        int x = 1 + 2 * pos[i]->dst_x ;
        int y = 2 + 4 * pos[i]->dst_y ;
        mvprintw(x, y, ".") ;
    }

    refresh() ;

    napms(1000) ;

    attroff(A_BLINK) ;

    refresh() ;

    int ch = getch() ;
    clear() ;

    return ch ;
}