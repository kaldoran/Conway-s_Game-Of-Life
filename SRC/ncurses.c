#include <stdio.h>
#include <curses.h>

void initNCurses() {
    initscr();
    noecho();
}


void endNCurses() {
    printw("End of generation\nUse anykey for leave\n");
    refresh();
    getch();
    endwin();
}
