#include <stdio.h>
#include <curses.h>

void initNCurses() {
	#if !defined(NCURSES) || !defined(PRINT)
		return; 
	#endif
	initscr();
	noecho();
}


void endNCurses() {
	#if !defined(NCURSES) || !defined(PRINT)
		return;
	#endif
	printw("End of generation\nUse anykey for leave\n");
	refresh();
	getch();
	endwin();
}
