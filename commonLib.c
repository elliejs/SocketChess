void initSocket(int* socket) {
  //catch socket creation error
  if ((*socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket creation error\n");
    exit(EXIT_FAILURE);
  }
}
