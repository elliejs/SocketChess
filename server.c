#include <stdlib.h>
#include <stdio.h>

#include "commonLib.h"
#include "serverLib.h"

int main(int argc, char const *argv[]) {
  int serv_socket = 0; //this holds the integer FD for finding the server socket file
  struct sockaddr_in serv_addr; //holds the actual internet address

  initServer(&serv_socket, &serv_addr);

  struct pollfd *connections;
  stack freeIndicies = NULL;
  nfds_t nfds = addConn(serv_socket, connections, 0, &freeIndicies);

  while(1) {
    if (poll(connections, nfds, 0) <= 0) {
      printf("poll returned error or no clients are ready. Cycling...\n")
      continue;
    }

    for (int i = 0; i < nfds; i++) {
        if (connections[i].revents & POLLIN) {
          connections[i].revents = 0;
          //do stuf...
        }
    }

  }

  return 0;
}
