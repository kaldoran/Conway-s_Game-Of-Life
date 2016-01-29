#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>

#include "game.h"
#include "ncurses.h"

Game* loadBoard() { Game* g = NULL; return g; }

void usage(char* name) {
	printf("%s <total tick> <file configuration>\n", name);
	printf("\t<total tick> : total generation needed\n");
	printf("\t<file configuration> : Location of the file to load\n");
	
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {

	srand(time(NULL));

	int max_tick = -1; 
	Game* g = NULL; 

	if ( argc == 1 ) usage(argv[0]);           // No arg - print manual
	if ( argc >= 2 ) max_tick = atoi(argv[1]); // Use total tick if given
	if ( argc >= 3 ) g = loadBoard(argv[2]);   // Use file if given
	
	// If none given then generate one
	if ( g == NULL ) g = generateRandomBoard(); 

	initNCurses();
	
	while(max_tick != 0) {         // Inifinit loop if total tick not given
		gameTick(g);       		   // Lets the game tick
		#ifdef NCURSES
			gamePrint(g, printw);
		#else
			gamePrint(g, printf);
		#endif
		--max_tick;
		usleep(500000);
	}


	endNCurses();	
	freeGame(g);           // Free space we are not in Java
	
	exit(EXIT_SUCCESS);
}

