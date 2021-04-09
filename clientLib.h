#ifndef CLIENT_LIB
#define CLIENT_LIB

#define HELP_MSG "run as ./chess [nickname] or ./chess [nickname] [server IP]\nOnce the server is running\n"

int initClient(int* socket, struct sockaddr_in* addr, const char* addr_str);
void connectWithRetry(int* socket, struct sockaddr_in* serv_addr, int maxAttempts);

#endif
