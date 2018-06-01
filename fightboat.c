/*******************************************************
*
*	name: fightboat
*	desc: implementation of battleships in ncurses
*	file: fightboat.c fightboat.h
*	auth: rory
*
*******************************************************/

/* imports */
#include "fightboat.h"

int main()
{
    init_curses(); // start the curses window
    print_logo(); // print the logo
    game_setup(); // get user input for game setup

    wrap_up(); // close curses window
    return 0; // clean exit
}

void init_curses()
{
    initscr(); // creates stdscr
    cbreak(); // allows exiting of the program with C-z or C-c
    keypad(stdscr, 1);
    noecho(); // turn off character echoing
}

void wrap_up()
{
    curs_set(1); // reset cursor pos
    clear(); // clear the display
    endwin(); // close (free memory of) stdscr and ends curses session
}

void print_logo()
{
    clear();
    printw(" _____  ____   ____  __ __  ______  ____    ___    ____  ______ \n");
    printw("|     |l    j /    T|  T  T|      T|    \\  /   \\  /    T|      T\n");
    printw("|   __j |  T Y   __j|  l  ||      ||  o  )Y     YY  o  ||      |\n");
    printw("|  l_   |  | |  T  ||  _  |l_j  l_j|     T|  O  ||     |l_j  l_j\n");
    printw("|   _]  |  | |  l_ ||  |  |  |  |  |  O  ||     ||  _  |  |  |  \n");
    printw("|  T    j  l |     ||  |  |  |  |  |     |l     !|  |  |  |  |  \n");
    printw("l__j   |____jl___,_jl__j__j  l__j  l_____j \\___/ l__j__j  l__j  \n");
    printw("\nPress ENTER to continue....");
    getch();
}

void game_setup()
{
    clear();
    int ch;
    int highlight = 1;
    int i;
    char choices[2][50];
    sprintf(choices[0], "HOST");
    sprintf(choices[1], "JOIN");
    printw("Are you hosting or joining a match?\n");
    while (1) {
        for (i = 1; i < 3; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(i + 1, 1, choices[i - 1]);
            attroff(A_REVERSE);
        }
        refresh();
        ch = getch();
        switch(ch) {
            case KEY_UP: highlight = 1; break;
            case KEY_DOWN: highlight = 2; break;
            default: break;
        }
        if (ch == ENTER_KEY) {
            break;
        }
    }

    if (highlight == 1) { // hosting the match
        host_game();
    } else { // joining a match
        join_game();
    }
}

void host_game()
{
    clear();
    printw("Enter port number (leave blank for default [6174]): ");
    int py, px;
    getyx(stdscr, py, px);
    char ch_port[64] = "6174";
    int i = 0;
    char ch;
    while (1) {
        if ((ch = getch()) != ENTER_KEY) {
            int y, x;
            getyx(stdscr, y, x);
            if (ch == BACKSPACE_KEY) {
                if (x > px) {
                    mvdelch(y, x - 1);
                    ch_port[--i] = '\0';
                }
            } else {
                ch_port[i++] = ch;
                printw("%c", ch);
            }
        } else {
            break;
        }
        refresh();
    }
    int port = atoi(ch_port);
    clear();
    printw("If you and your friend are not on the same LAN (i.e. you are connecting over the internet),\n");
    printw("please make sure you have port %d forwarded on your router!\n", port);
    printw("\nNow awaiting connection....");

    // create serverside socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;

    getch();
}

void join_game()
{
    clear();
}
