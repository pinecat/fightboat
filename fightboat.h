#ifndef FIGHTBOAT_H
#define FIGHTBOAT_H

/* imports */
// std
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <curses.h>

// networking
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

/* constants */
#define PORT 6174 // 61 - a in hex, 74 - t in hex (see boat in hex)
#define LO_PORT 1025
#define HI_PORT 65535
#define IP "127.0.0.1"
#define ENTER_KEY 10
#define BACKSPACE_KEY 7

/* prototypes */
void init_curses();
void wrap_up();
void print_logo();
void game_setup();

void host_game();
void print_board(char gamebaord[12][512]);
void join_game();

#endif
