void initServer(int* socket, struct sockaddr_in* addr) {
  initSocket(socket);
  int opt = true;
  if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
    perror("ERROR on sockoption reuse addr");
    exit(EXIT_FAILURE);
  }

  bzero((char *)addr, sizeof(*addr)); //zero out for safety
  addr->sin_family = AF_INET;
  addr->sin_port = htons(PORT);
  addr->sin_addr.s_addr = INADDR_ANY;

  if (bind(socket, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
    error("ERROR on binding");
    exit(EXIT_FAILURE);
  }

  if(listen(socket, 5) > 0) {
    perror("ERROR on listen");
    exit(EXIT_FAILURE);
  }
}

ndfs_t addConn(int socket, struct pollfd *connections, nfds_t nfds, stack *freeIndicies) {
  int here = pop(freeIndicies);
  if(here < 0) {
    here = nfds;
    realloc(connections, ++nfds * sizeof(struct pollfd));
  }
  connections[here].fd = socket;
  connections[here].events = POLLIN;
  return nfds;
}

void removeConn(int socket, struct pollfd *connections, nfds_t nfds, stack *freeIndicies) {
  //backwards loop because maybe more efficient
  for(int i = nfds - 1; i >= 0; i--) {
    if (connections[i].fd == socket) {
      connections[i].fd = -1;
      push(freeIndicies, i);
      return;
    }
  }
}

void push(stack* stk, int i) {
  stack elem = malloc(sizeof(struct element));
  elem->idx = i;
  elem->next = *stk;
  *stk = elem;
}

int pop(stack* stk) {
  if (*stk == NULL) return -1;
  else {
    int idx = (*stk)->idx;
    stack next = (*stk)->next;
    free(*stk);
    *stk = next;
    return idx;
  }
}
