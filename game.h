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

void next_pos_move (int board[8][8], int color, Coordinate * coord[64]) ;