#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include "network.h"

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "-server") == 0 && argc == 3) {
        serv_main(argv[2]) ;
    } else if (strcmp(argv[1], "-client") == 0 && argc == 4) {
        clnt_main(argv[2], argv[3]) ;
    } else {
        fprintf(stderr, "Usage: ./reversi -server <port>\n") ;
        fprintf(stderr, "Usage: ./reversi -client <ip> <port>\n") ;
		exit(EXIT_FAILURE) ;
    }
}