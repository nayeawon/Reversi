#include <ncurses.h>
#include <ctype.h>
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

int next_move(int board[8][8], Coordinate * pos[64], int color)
{
    char * color_str = (color == BLACK) ? "0" : "O" ;
    // Enable attributes for blinking text
    attron(A_BLINK);
    int x_pos [32];
    int y_pos [32];
    int cnt = 0 ;
    for (int i = 0 ; i < 64 ; i++) {
        if (pos[i] == NULL)
            break ;
        int row = 1 + 2 * pos[i]->dst_x ;
        int col = 2 + 4 * pos[i]->dst_y ;
        mvprintw(row, col, ".") ;
        x_pos[cnt] = row ;
        y_pos[cnt] = col ;
        cnt++ ;
    }

    refresh() ;

    napms(1000) ;

    attroff(A_BLINK) ;

    refresh() ;
    int x = 1 + 2 * pos[0]->dst_x ;
    int y = 2 + 4 * pos[0]->dst_y ;
    move(x, y) ;
    refresh() ;
    int c ;
    while (c = getch()) {
		switch (c) {
			case KEY_UP:
				x = x - 2 ;
				break ;

			case KEY_DOWN:
				x = x + 2 ;
				break ;

			case KEY_LEFT:
				y  = y - 4 ;
				break ;

			case KEY_RIGHT:
				y = y + 4 ;
				break ;

			default:
				break ;
		}
        if (x < 1) x = 1 ;
        if (x > 15) x = 15 ;
        if (y < 2) y = 2 ;
        if (y > 30) y = 30 ;
        move(x, y) ;
        
        refresh() ;
        char * ch = (char *)malloc(sizeof(char)) ;
        sprintf(ch, "%c", c) ;
        if (c != KEY_UP && c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT) {
            if (strcmp(color_str, ch) == 0) {
                int check = 0 ;
                for (int i = 0 ; i < cnt ; i++) {
                    if (x == x_pos[i] && y == y_pos[i])
                        check = 1 ;
                }
                if (check) break ;
                mvprintw(17, 0, "You can't put it there!\n") ;
                napms(1000) ;
                move(0, 0) ;
            }
            else {
                mvprintw(17, 0, "Please enter %s\n", color_str) ;
                napms(1000) ;
                move(0, 0) ;
            }
            display(board) ;
            attron(A_BLINK);
            for (int i = 0 ; i < 64 ; i++) {
                if (pos[i] == NULL)
                    break ;
                int row = 1 + 2 * pos[i]->dst_x ;
                int col = 2 + 4 * pos[i]->dst_y ;
                mvprintw(row, col, ".") ;
            }
            refresh() ;

            napms(1000) ;

            attroff(A_BLINK) ;

            refresh() ;

            int x = 1 + 2 * pos[0]->dst_x ;
            int y = 2 + 4 * pos[0]->dst_y ;
            move(x, y) ;
        }
    }
    return c ;
}



void display_new(int * verified_input, int changes[8], int color, int (* old_board)[8])
{
    // Todo : display the last changes made in new_board (user input)
    clear() ;
    display(old_board) ;
    char * c = (color == WHITE) ? "O" : "0" ;
    int x, y ;
    for (int i = 0 ; i < 8 ; i++) {
        if (changes[i] == -1) continue;
        switch (type) {
        case HORIZONTAL:
            x = changes[i] ;
            y = i ;
            old_board[x][y] = color ;
            mvprintw(1 + 2 * x, 2 + 4 * y, c) ;
            napms(1000) ;
            refresh() ;
            break;
        case VERTICAL:
            x = i ;
            y = changes[i] ;
            old_board[x][y] = color ;
            mvprintw(1 + 2 * x, 2 + 4 * y, c) ;
            napms(1000) ;
            refresh() ;
            break;
        case U_DIAG:
            x = i ;
            y = changes[i] ;
            old_board[x][y] = color ;
            mvprintw(1 + 2 * x, 2 + 4 * y, c) ;
            napms(1000) ;
            refresh() ;
            break;
        case D_DIAG:
            x = i ;
            y = changes[i] ;
            old_board[x][y] = color ;
            mvprintw(1 + 2 * x, 2 + 4 * y, c) ;
            napms(1000) ;
            refresh() ;
            break;
        default:
            break;
        }
    }
}