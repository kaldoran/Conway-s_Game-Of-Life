#include <stdio.h>
#include <curses.h>

void initNCurses() {
	initscr();
	noecho();
}


void endNCurses() {
	getch();
	endwin();
}
