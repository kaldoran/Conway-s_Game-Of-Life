#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>

#include "error.h"
#include "game.h"
#include "ncurses.h"

void usage(char* name) {
	printf("%s <total tick> <file configuration>\n", name);
	printf("\t<total tick> : total generation needed\n");
	printf("\t<file configuration> : Location of the file to load\n");
	
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {

	srand(time(NULL));
	int (*printFunc)(const char*, ...);	
	printFunc = 
		#ifdef NCURSES 
			&printw;
		#else 
			&printf; 
		#endif
	int max_tick = -1; 
	Game* g = NULL; 

	//if ( argc == 1 ) usage(argv[0]);           // No arg - print manual
	if ( argc >= 2 ) max_tick = atoi(argv[1]); // Use total tick if given
	if ( argc >= 3 ) g = loadBoard(argv[2]);   // Use file if given

	// If none given then generate one
	if ( g == NULL ) g = generateRandomBoard(); 

	initNCurses();
	
	while(max_tick != 0) {         // Inifinit loop if total tick not given
		#ifdef NCURSES
			printFunc("%d Generation left.\n", max_tick);
			gamePrint(g, printFunc);
		#else
			printFunc("%d Generation left.\n", max_tick);
			gamePrint(g, printFunc);
		#endif
		gameTick(g);       		   // Lets the game tick
		--max_tick;
		usleep(400000);
	}

	endNCurses();
	freeGame(g);           // Free space we are not in Java
	
	exit(EXIT_SUCCESS);
}

