#include <stdio.h>
#include <curses.h>

void initNCurses() {
	#ifndef NCURSES 
		return; 
	#endif
	initscr();
	noecho();
}


void endNCurses() {
	#ifndef NCURSES 
		return;
	#endif
	printw("End of generation\nUse anykey for leave\n");
	refresh();
	getch();
	endwin();
}
