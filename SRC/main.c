#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>

#include "error.h"
#include "game.h"
#include "ncurses.h"
#include "option.h"

int main(int argc, char* argv[]) {

	srand(time(NULL));

	Option o;
	Game* g = NULL; 
	
	o = getOption(argc, argv);									// Get all option
	if ( *o.file_path != '\0' ) g = loadBoard(o.file_path);     // Use file if given

	if ( g == NULL ) g = generateRandomBoard(); 	            // if load fail or no grid given
	if ( o.use_ncurses ) initNCurses();

	while(o.max_tick != 0) {         // Inifinit loop if total tick not given
		gamePrintInfo(g, o);
		gameTick(g);       		   // Lets the game tick
		__swapGrid(g);
		--o.max_tick;
		#ifdef PRINT 
			usleep(400000);
		#endif
	}
	
	if ( o.use_ncurses) endNCurses();

	freeGame(g);           // Free space we are not in Java
	
	exit(EXIT_SUCCESS);
}

