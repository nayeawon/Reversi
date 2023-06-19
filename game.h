#define WHITE 1
#define BLACK 0

typedef struct {
    int turn_cnt ;
    int turn_over ;
    int move_x ;
    int move_y ;
} Turn ;

typedef enum { HORIZONTAL=0, VERTICAL, U_DIAG, D_DIAG } Type ;

typedef struct {
    Type type ;
    int src_x ;
    int src_y ;
    int dst_x ;
    int dst_y ;
} Coordinate ;

/* send a current board to the opponent */
char * to_string(int board[8][8]) ;

/* receive the opponent's current board */
void to_board(char * str, int (* board)[8]) ;

/* next possible move */
void next_pos_move (int board[8][8], int color, Coordinate * coord[64]) ;

/* verify user input by possible move */
Coordinate * verify(int board[8][8], Coordinate * pos[64], int x, int y) ;

/* copy board */
void copy_board(int (* new_board)[8], int (* board)[8]) ;

/* calculate new board based on the user input */
void new_board(int (* board)[8], int * change, int color, Coordinate * verified_input) ;