#include <stdlib.h>
#include <stdio.h>

#include <ncurses.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdbool.h>
#include <string.h>

#include <signal.h>

#include "commonLib.h"
#include "clientLib.h"

// void beginChess();

void initNCURSES(WINDOW *header, WINDOW *typer, WINDOW *main) {
  initscr();              //init ncurses for GUI library
  raw();                  //ctrl+C won't save you
  keypad(stdscr, TRUE);   //get arrows and F keys
  noecho();               //closer control over how characters typed get displayed
  nodelay(stdscr, true);  //nonblocking getch()
}

int main(int argc, char const *argv[]) {
  //begin server connection
  int socket = 0;
  struct sockaddr_in serv_addr;
  bool solo = false, connected = false;

  if (argc < 2 || !strcmp(argv[1], "help")
               || !strcmp(argv[1], "-h")
               || !strcmp(argv[1], "--help")) {
    printf(HELP_MSG);
    exit(EXIT_FAILURE);
  } else if (argc == 2) {
    solo = true;
    printf("starting solo game...\n");
  } else {
    printf("starting server game...\n")
    initClient(&socket, &serv_addr, argv[1]);
  }

  WINDOW *header, *typer, *main;
  initNCURSES(header, typer, main);

  if (solo) {

  } else {
    char quitKeys[] = {'Q'};
    if (!setupQuit(quitKeys, 1)) exit(EXIT_FAILURE);
    connectWithRetry(&socket, &serv_addr, 3);
  }

  exit(EXIT_SUCCESS);
}

// void beginChess() {
//   int row, col;
//   do {
//     getmaxyx(stdscr, row, col); //collect row and column info for screen manipulation
//     mvprintw(1, 0, "Please resize your window to at least %d characters tall\nCurrent size %d x %d", (6 + MIN_BOARD_SIZE), row, col);
//   } while (row < (6 + MIN_BOARD_SIZE)); //while screen can't actually display game, demand resize
//
//   WINDOW  *header = newwin(3, col, row, 0), //top window for header. Turn info etc...
//           *typer  = newwin(3, col, 3, 0), //typer window to show players input to the game. Moves / commands etc...
//           *board  = newwin(row - 6, col, )
// }


//	delwin(win);
