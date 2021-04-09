int initClient(int* socket, struct sockaddr_in* addr, const char* addr_str) {
  initSocket(socket);
  bzero((char *) addr, sizeof(*addr));
  addr->sin_family = AF_INET;
  addr->sin_port = htons(PORT);
  if (!inet_pton(AF_INET, addr_str, addr->sin_addr)) {
		printf("Invalid address / Address not supported\n\n");
    printf(HELP_MSG);
		exit(EXIT_FAILURE);
	}
}

void connectWithRetry(int* socket, struct sockaddr_in* serv_addr, int maxAttempts) {
  for(int attempt = 1; //starting at attempt 1
      attempt <= maxAttempts && //while not at maxAttempts AND
      connect(socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0; //still not connected
      attempt++) { //increase attempt and try again
    mvprintw(0, 0, "Connection Failed. Retrying... Attempt: %d", attempt);
    refresh();
    sleep(3);
  }
}

// void cleanup() {
//   endwin();
//   exit(EXIT_FAILURE);
// }
//
// forkID sfork() {
//   int f = fork();
//   if (f < 0) {
//     return FAIL;
//   } else if (f == 0) {
//     return CHILD;
//   } else {
//     return PARENT;
//   }
// }
//
// bool setupQuit(char* chars, int n) {
//   signal(SIGCHLD, cleanup);
//   switch(sfork()) {
//     case FAIL:
//       perror("Quit failed to initialize. Killing program as it is unsafe to continue.");
//       return false;
//     case CHILD:
//       FOREVER {
//         char ch = getch();
//         for (int i = 0; i < n; i++) {
//           if (ch == chars[i]) {
//             exit(EXIT_SUCCESS);
//           }
//         }
//       }
//     case PARENT:
//       break;
//   }
//   return true;
// }
