int serv_init(char * port) ;

void serv_play(int conn_fd) ;

void serv_main(char* port) ;

int clnt_init(const char * ip, int port) ;

void clnt_play(int conn_fd) ;

void clnt_main(char* ip, char* port) ;
