#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game.h"

char * to_string(int board[8][8]) 
{
    char * str = (char *)malloc(sizeof(char) * 81) ;
    char tmp[2] ;
    strcpy(str, "") ;
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            sprintf(tmp, "%d,", board[i][j]) ;
            strcat(str, tmp);
        }
        strcat(str, "\n") ;
    }
    str[strlen(str)] = '\0' ;
    return str ;
}

void to_board(char * str, int (* board)[8])
{
    char * token = strtok(str, ",") ;
    int i = 0 ;
    int j = 0 ;
    while (token != NULL) {
        board[i][j] = atoi(token) ;
        token = strtok(NULL, ",\n") ;
        j++ ;
        if (j == 8) {
            j = 0 ;
            i++ ;
        }
    }
}

void next_pos_move (int board[8][8], int color, Coordinate * coord[64])
{
    int target = (color == WHITE) ? BLACK : WHITE ;
    int cnt = 0 ;
    
    for (int i = 0; i < 64; i++) {
        coord[i] = (Coordinate *)malloc(sizeof(Coordinate));
    }
    /* Horizontal */
    for (int i = 0 ; i < 8 ; i++) {
        int pos = 0 ;
        while (pos < 8) {
            while (board[i][pos] != color && pos < 8)
                pos++ ;
            if (pos == 7)
                break ;
            if (pos > 1 && board[i][pos-1] == target) {
                int j = pos-2 ;
                while (j >= 0 && board[i][j] == target)
                    j-- ;
                if (j >= 0 && board[i][j] == -1) {
                    coord[cnt] = (Coordinate *) malloc(sizeof(Coordinate)) ;
                    coord[cnt]->type = HORIZONTAL ;
                    coord[cnt]->src_x = i ;
                    coord[cnt]->src_y = pos ;
                    coord[cnt]->dst_x = i ;
                    coord[cnt]->dst_y = j ;
                    cnt++ ;
                }
            }
            if (pos < 6 && board[i][pos+1] == target) {
                int j = pos+2 ;
                while (j < 8 && board[i][j] == target)
                    j++ ;
                if (j < 8 && board[i][j] == -1) {
                    coord[cnt] = (Coordinate *) malloc(sizeof(Coordinate)) ;
                    coord[cnt]->type = HORIZONTAL ;
                    coord[cnt]->src_x = i ;
                    coord[cnt]->src_y = pos ;
                    coord[cnt]->dst_x = i ;
                    coord[cnt]->dst_y = j ;
                    cnt++ ;
                }
            }
            pos++ ;
        }
    }
    
    /* Vertical */
    for (int j = 0 ; j < 8 ; j++) {
        int pos = 0 ;
        while (pos < 8) {
            while (board[pos][j] != color && pos < 8)
                pos++ ;
            if (pos == 7)
                break ;
            if (pos > 1 && board[pos-1][j] == target) {
                int i = pos-2 ;
                while (i > 0 && board[i][j] == target)
                    i-- ;
                if (i >= 0 && board[i][j] == -1) {
                    printf("cnt = %d\n", cnt);
                    coord[cnt] = (Coordinate *) malloc(sizeof(Coordinate)) ;
                    printf("%d %d %d %d\n", pos, j, i, j);
                    coord[cnt]->type = VERTICAL ;
                    coord[cnt]->src_x = pos ;
                    coord[cnt]->src_y = j ;
                    coord[cnt]->dst_x = i ;
                    coord[cnt]->dst_y = j ;
                    cnt++ ;
                }
            }
            else if (pos < 6 && board[pos+1][j] == target) {
                int i = pos+2 ;
                while (i < 8 && board[i][j] == target)
                    i++ ;
                if (i < 8 && board[i][j] == -1) {
                    coord[cnt] = (Coordinate *) malloc(sizeof(Coordinate)) ;
                    printf("%d %d %d %d\n", pos, j, i, j);
                    coord[cnt]->type = VERTICAL ;
                    coord[cnt]->src_x = pos ;
                    coord[cnt]->src_y = j ;
                    coord[cnt]->dst_x = i ;
                    coord[cnt]->dst_y = j ;
                    cnt++ ;
                }
            }
            pos++ ;
        }
    }

    /* Upper Diagonal */
    for (int n = 2 ; n <= 12 ; n++) {
        int x_pos = 0 ;
        int y_pos = n - x_pos ;
        while (x_pos < 8 && y_pos >= 0) {
            while (board[x_pos][y_pos] != color && x_pos < 8 && y_pos >= 0) {
                x_pos++ ;
                y_pos-- ;
            }
            if (x_pos == 7 || y_pos <= 0)
                break ;
            if ((x_pos > 1 && y_pos < 6) && board[x_pos-1][y_pos+1] == target) {
                int i = x_pos-2 ;
                int j = y_pos+2 ;
                while (i >= 0 && j < 8 && board[i][j] == target) {
                    i-- ;
                    j++ ;
                }
                if (i >= 0 && j < 8 && board[i][j] == -1) {
                    coord[cnt] = (Coordinate *) malloc(sizeof(Coordinate)) ;
                    coord[cnt]->type = U_DIAG ;
                    coord[cnt]->src_x = x_pos ;
                    coord[cnt]->src_y = y_pos ;
                    coord[cnt]->dst_x = i ;
                    coord[cnt]->dst_y = j ;
                    cnt++ ;
                }
            }
            if ((x_pos < 6 && y_pos > 1) && board[x_pos+1][y_pos-1] == target) {
                int i = x_pos+2 ;
                int j = y_pos-2 ;
                while (i < 8 && j >= 0 && board[i][j] == target) {
                    i++ ;
                    j-- ;
                }
                if (i < 8 && j >= 0 && board[i][j] == -1) {
                    coord[cnt] = (Coordinate *) malloc(sizeof(Coordinate)) ;
                    coord[cnt]->type = U_DIAG ;
                    coord[cnt]->src_x = x_pos ;
                    coord[cnt]->src_y = y_pos ;
                    coord[cnt]->dst_x = i ;
                    coord[cnt]->dst_y = j ;
                    cnt++ ;
                }
            }
            x_pos++ ;
            y_pos-- ;
        }

    /* Lower Diagonal */
    for (int i = -5 ; i < 6 ; i++) {
        int x_pos, y_pos ;
        if (i < 0) {
            x_pos = i * -1 ;
            y_pos = 0 ;
        }
        else {
            x_pos = 0 ;
            y_pos = i ;
        }
        while (x_pos < 8 && y_pos < 8) {
            while (board[x_pos][y_pos] != color && x_pos < 8 && y_pos < 8) {
                x_pos++ ;
                y_pos++ ;
            }
            if (x_pos == 7 || y_pos == 7)
                break ;
            if ((x_pos > 1 && y_pos > 6) && board[x_pos-1][y_pos-1] == target) {
                int i = x_pos-2 ;
                int j = y_pos-2 ;
                while (i > 0 && j < 8 && board[i][j] == target) {
                    i-- ;
                    j-- ;
                }
                if (i >= 0 && j >= 0 && board[i][j] == -1) {
                    coord[cnt] = (Coordinate *) malloc(sizeof(Coordinate)) ;
                    coord[cnt]->type = D_DIAG ;
                    coord[cnt]->src_x = x_pos ;
                    coord[cnt]->src_y = y_pos ;
                    coord[cnt]->dst_x = i ;
                    coord[cnt]->dst_y = j ;
                    cnt++ ;
                }
            }
            if ((x_pos < 6 && y_pos < 6) && board[x_pos+1][y_pos+1] == target) {
                int i = x_pos+2 ;
                int j = y_pos+2 ;
                while (i < 8 && j < 8 && board[i][j] == target) {
                    i++ ;
                    j++ ;
                }
                if (i < 8 && j < 8 && board[i][j] == -1) {
                    coord[cnt] = (Coordinate *) malloc(sizeof(Coordinate)) ;
                    coord[cnt]->type = D_DIAG ;
                    coord[cnt]->src_x = x_pos ;
                    coord[cnt]->src_y = y_pos ;
                    coord[cnt]->dst_x = i ;
                    coord[cnt]->dst_y = j ;
                    cnt++ ;
                }
            }
            x_pos++ ;
            y_pos++ ;
        }
        }
    }
    coord[cnt] = NULL ;
}

Coordinate * verify(int board[8][8], Coordinate * pos[64], int x, int y)
{
    int row = (x-1)/2 ;
    int col = (y-2)/4 ;
    for (int i = 0 ; i < 64 ; i++) {
        if (pos[i] == NULL)
            break ;
        if (pos[i]->dst_x == row && pos[i]->dst_y == col) {
            return pos[i] ;
        }
    }
    return NULL ;
}

void copy_board(int (* new_board)[8], int (* board)[8])
{
    for (int i = 0 ; i < 8 ; i++) {
        for (int j = 0 ; j < 8 ; j++) {
            new_board[i][j] = board[i][j] ;
        }
    }
}

void new_board(int (* board)[8], int * change, int color, Coordinate * verified_input)
{
    int x = verified_input->dst_x ;
    int y = verified_input->dst_y ;
    Type type = verified_input->type ;
    int src_x = verified_input->src_x ;
    int src_y = verified_input->src_y ;
    board[x][y] = color ;
    int cnt = 0 ;
    printf("type = %d\n", type) ;
    if (type == HORIZONTAL) {
        if (src_y < y) {
            for (int i = src_y+1 ; i < y ; i++) {
                board[x][i] = color ;
                change[i] = x ;
            }
        }
        else {
            for (int i = src_y-1 ; i > y ; i--) {
                board[x][i] = color ;
                change[i] = x ;
            }
        }
        change[y] = x ;
    }
    else if (type == VERTICAL) {
        if (src_x < x) {
            for (int i = src_x+1 ; i < x ; i++) {
                board[i][y] = color ;
                change[i] = y ;
            }
        }
        else {
            for (int i = src_x-1 ; i > x ; i--) {
                board[i][y] = color ;
                change[i] = y ;
            }
        }
        change[x] = y ;
    }
    else if (type == U_DIAG) {
        if (src_x > x && src_y < y) {
            int i = src_x-1 ;
            int j = src_y+1 ;
            while (i > x && j < y) {
                board[i][j] = color ;
                change[i] = j ;
                i-- ;
                j++ ;
            }
        }
        if (src_x < x && src_y > y) {
            int i = src_x+1 ;
            int j = src_y-1 ;
            while (i < x && j > y) {
                board[i][j] = color ;
                change[i] = j ;
                i++ ;
                j-- ;
            }
        }
        change[x] = y ;
    }
    else if (type == D_DIAG) {
        if (src_x < x && src_y < y) {
            int i = src_x + 1;
            int j = src_y + 1;
            while (i < x && j < y) {
                board[i][j] = color;
                change[i] = j;
                i++;
                j++;
            }
        }
        if (src_x > x && src_y > y) {
            int i = src_x - 1;
            int j = src_y - 1;
            while (i > x && j > y) {
                board[i][j] = color;
                change[i] = j;
                i--;
                j--;
            }
        }

        change[x] = y ;
    }
}