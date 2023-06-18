#include <stdlib.h>
#include <stdio.h>
#include "game.h"

void next_pos_move (int board[8][8], int color, Coordinate * coord[64])
{
    int target = (color == WHITE) ? BLACK : WHITE ;
    int cnt = 0 ;
    
    /* Horizontal */
    for (int i = 0 ; i < 8 ; i++) {
        int pos = 0 ;
        while (board[i][pos] != color && pos < 8)
            pos++ ;
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
    }

    /* Vertical */
    for (int j = 0 ; j < 8 ; j++) {
        int pos = 0 ;
        while (board[pos][j] != color && pos < 8)
            pos++ ;
        if (pos > 1 && board[pos-1][j] == target) {
            int i = pos-2 ;
            while (i >= 0 && board[i][j] == target)
                i-- ;
            if (i >= 0 && board[i][j] == -1) {
                coord[cnt] = (Coordinate *) malloc(sizeof(Coordinate)) ;
                coord[cnt]->type = VERTICAL ;
                coord[cnt]->src_x = pos ;
                coord[cnt]->src_y = j ;
                coord[cnt]->dst_x = i ;
                coord[cnt]->dst_y = j ;
                cnt++ ;
            }
        }
        if (pos < 6 && board[pos+1][j] == target) {
            int i = pos+2 ;
            while (i < 8 && board[i][j] == target)
                i++ ;
            if (i < 8 && board[i][j] == -1) {
                coord[cnt] = (Coordinate *) malloc(sizeof(Coordinate)) ;
                coord[cnt]->type = VERTICAL ;
                coord[cnt]->src_x = pos ;
                coord[cnt]->src_y = j ;
                coord[cnt]->dst_x = i ;
                coord[cnt]->dst_y = j ;
                cnt++ ;
            }
        }
    }

    /* Upper Diagonal */
    for (int n = 2 ; n <= 12 ; n++) {
        int x_pos = 0 ;
        int y_pos = n - x_pos ;
        while (board[x_pos][y_pos] != color && x_pos < 8 && y_pos >= 0) {
            x_pos++ ;
            y_pos-- ;
        }
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
        while (board[x_pos][y_pos] != color && x_pos < 8 && y_pos < 8) {
            x_pos++ ;
            y_pos++ ;
        }
        if ((x_pos > 1 && y_pos < 6) && board[x_pos-1][y_pos+1] == target) {
            int i = x_pos-2 ;
            int j = y_pos+2 ;
            while (i >= 0 && j < 8 && board[i][j] == target) {
                i-- ;
                j++ ;
            }
            if (i >= 0 && j < 8 && board[i][j] == -1) {
                coord[cnt] = (Coordinate *) malloc(sizeof(Coordinate)) ;
                coord[cnt]->type = D_DIAG ;
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
                coord[cnt]->type = D_DIAG ;
                coord[cnt]->src_x = x_pos ;
                coord[cnt]->src_y = y_pos ;
                coord[cnt]->dst_x = i ;
                coord[cnt]->dst_y = j ;
                cnt++ ;
            }
        }
    }

}

