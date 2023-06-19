/* print out the board */
void display(int board[8][8]) ;

/* indicate the next move that user can select */
int next_move(int board[8][8], Coordinate * pos[64], int color) ;

/* gradually show the change of board */
void display_new(Type type, int changes[8], int color, int (* old_board)[8]) ;