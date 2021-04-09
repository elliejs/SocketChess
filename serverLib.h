#ifndef SERVER_LIB
#define SERVER_LIB

typedef struct element* stack;

struct element {
  int idx;
  stack next;
};

void initServer(int* socket, struct sockaddr_in* addr);
ndfs_t addConn(int socket, struct pollfd *connections, nfds_t nfds, stack *freeIndicies);
void removeConn(int socket, struct pollfd *connections, nfds_t nfds, stack *freeIndicies);

void push(stack *stk, int i);
int pop(stack *stk);

#endif
