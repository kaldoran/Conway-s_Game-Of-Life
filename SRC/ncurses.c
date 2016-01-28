#include <stdio.h>
#include <curses.h>

void initNCurses() {
	initscr();
	noecho();

	endwin();
}


void endNCurses() {
	printw("End of generation\nPress any key for exit\n");
	getch();
	endwin();
}
