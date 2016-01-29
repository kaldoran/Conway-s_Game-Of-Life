#include <stdio.h>
#include <curses.h>

void initNCurses() {
	#ifndef NCURSES 
		return; 
	#endif
	fprintf(stderr, "YOLO");
	initscr();
	noecho();
}


void endNCurses() {
	#ifndef NCURSES 
		return;
	#endif
	getch();
	endwin();
}
