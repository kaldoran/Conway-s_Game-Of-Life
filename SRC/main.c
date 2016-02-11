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
#include "thread.h"

int main(int argc, char* argv[]) {

	srand(time(NULL));

	Option o;
	Game* g = NULL; 
	TickParam *tp = NULL;

	o = getOption(argc, argv);									// Get all option	
	if ( *o.file_path != '\0' ) g = loadBoard(o.file_path);     // Use file if given

	if ( g == NULL ) g = generateRandomBoard(o); 	            // if load fail or no grid given
	if ( o.use_ncurses ) initNCurses();

	if ( o.nb_thread == 0 ) {
		tp = newTickParam(0, g->cols - 1, g);
	}

	fprintf(stderr, "USe : %d\n", o.use_fine_grained);
	while(o.max_tick != 0) {         // Inifinit loop if total tick not given
		gamePrintInfo(g, o);
		
		if ( o.nb_thread == 0 )      // if there is 0 thread then do not use thread method 
			gameTick(tp);       	 // Lets the game tick
		else
			createNThreadF(o.nb_thread, g, o.use_fine_grained);

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

