#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <ncurses.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <linux/socket.h>
#include "game.h"
#include "display.h"

int serv_init(char * port)
{
    // TCP connection
	int sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_adr;
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET; 
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(port));
	
	// bind and listen
	if (bind(sock_fd, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1) {
        perror("bind failed: "); 
		exit(EXIT_FAILURE); 
    }
		
	if (listen(sock_fd, 5) == -1) {
        perror("listen failed: "); 
        exit(EXIT_FAILURE);
    }
	int addrlen = sizeof(serv_adr); 
	int conn_fd = accept(sock_fd, (struct sockaddr *) &serv_adr, (socklen_t*)&addrlen) ;
    if (conn_fd < 0) {
		perror("accept failed: "); 
		exit(EXIT_FAILURE); 
	}
    return conn_fd ;
}

void serv_play(int conn_fd)
{
    /* initialize board */
    int board[8][8] ;
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            board[i][j] = -1 ;
        }
    }
    
    board[3][4] = WHITE ; board[4][3] = WHITE ; /* white */
    board[3][3] = BLACK ; board[4][4] = BLACK ; /* black */
    char buf[256] ;

    initscr();
    cbreak() ;
    keypad(stdscr, TRUE) ;    
    curs_set(2) ;

	do {
        clear();
		int s ;
		while ( (s = recv(conn_fd, buf, 255, 0)) == 0 ) ;
		if (s == -1)
			break ;

		buf[s] = '\0' ;
        to_board(buf, board) ;
        display(board) ; /* print board */
        Coordinate * pos[64] ;
        next_pos_move(board, WHITE, pos) ; /* calculate possible moves */
        int input = next_move(board, pos, WHITE) ; /* get input */
        int y, x ;
        getyx(stdscr, y, x) ; /* get cursor location */
        clear() ;
        Coordinate * verified_input = verify(board, pos, y, x) ; /* verify input */
        if (verified_input == 0x0) printf("invalid input\n") ;
		int old_board[8][8] ;
        copy_board(old_board, board) ;
        int (* ptr)[8] = board ;
        int changes[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
        int * ptr_changes = (int *)changes ;
        new_board(ptr, ptr_changes, WHITE, verified_input) ; /* calculate next board */
        int (* old_ptr)[8] = old_board ;
        display_new(verified_input->type, changes, WHITE, old_ptr) ; /* print next board */
        int row,col;
        getmaxyx(stdscr,row,col);
        
        strcpy(buf, to_string(board)) ;
        napms(1000) ;
		send(conn_fd, buf, strlen(buf), 0) ;
	} while (strcmp(buf, "quit()") != 0) ;
}

void serv_main(char * port) 
{
    int conn_fd = serv_init(port) ;
    serv_play(conn_fd) ;
    shutdown(conn_fd, SHUT_RDWR) ;
}

int clnt_init(const char * ip, int port)
{
    int sock_fd ;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0) ;
	if (sock_fd <= 0) {
		perror("socket failed : ") ;
		exit(EXIT_FAILURE) ;
	}
	int opt = 2 ;
	if (setsockopt(sock_fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt)) != 0) {
		fprintf(stderr, "fail at setsockopt\n") ;
		exit(EXIT_FAILURE) ;
	}

	struct sockaddr_in address ;
	bzero(&address, sizeof(address)) ;
	address.sin_family = AF_INET ; 
	address.sin_port = htons(port) ; 
	if (inet_pton(AF_INET, ip, &address.sin_addr) <= 0) {
		perror("inet_pton failed : ") ; 
		exit(EXIT_FAILURE) ;
	} 

	if (connect(sock_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
		perror("connect failed : ") ;
		exit(EXIT_FAILURE) ;
	}
	return sock_fd ;
}

void clnt_play(int conn_fd)
{
    /* initialize board */
    int board[8][8] ;
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            board[i][j] = -1 ;
        }
    }
    
    board[3][4] = 1 ; board[4][3] = 1 ; /* white */
    board[3][3] = 0 ; board[4][4] = 0 ; /* black */

    initscr();
    cbreak() ;
    keypad(stdscr, TRUE) ;    
    curs_set(2) ;

    char buf[256] ;

	do {
        clear() ; //?
        display(board) ; /* print board */
        Coordinate * pos[64] ;
        next_pos_move(board, BLACK, pos) ; /* calculate possible moves */
        int input = next_move(board, pos, BLACK) ; /* get input */
        int y, x ;
        getyx(stdscr, y, x) ; /* get cursor location */
        clear() ;
        Coordinate * verified_input = verify(board, pos, y, x) ; /* verify input */
        if (verified_input == 0x0) printf("invalid input\n") ;
        int old_board[8][8] ;
        copy_board(old_board, board) ;
        int (* ptr)[8] = board ;
        int changes[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
        int * ptr_changes = (int *)changes ;
        new_board(ptr, ptr_changes, BLACK, verified_input) ; /* calculate next board */
        int (* old_ptr)[8] = old_board ;
        display_new(verified_input->type, changes, BLACK, old_ptr) ; /* print next board */
        int row,col;
        getmaxyx(stdscr,row,col);
        
        // sending
        strcpy(buf, to_string(board)) ;
        napms(1000) ;
		// buf[strlen(buf) - 1] = '\0' ;

		send(conn_fd, buf, strlen(buf), 0) ;

		int s ;
		while ((s = recv(conn_fd, buf, 1024, 0)) == 0) ;
        napms(5000) ;
		if (s == -1)
			break ;
		buf[s] = '\0' ;
        to_board(buf, board) ;
	} while (strcmp(buf, "quit()") != 0) ;
}

void clnt_main(char * ip, char * port) 
{
    int conn_fd = clnt_init(ip, atoi(port)) ;
	
	clnt_play(conn_fd) ;

	shutdown(conn_fd, SHUT_RDWR) ;

	return EXIT_SUCCESS ;
}