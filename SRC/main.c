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

	o = getOption(argc, argv);  /* Get all option	 */

	if ( *o.file_path != '\0' ) /* If path file is not empty */
		g = loadBoard(o.file_path); /* then use the given file [load id] */

	if ( g == NULL ) /* If load of file fail Or no grid given */
		g = generateRandomBoard(o); /* then create one */

	if ( o.use_ncurses ) /* If we use ncurses */
		initNCurses();   /* Then we init the display */

	if ( o.nb_thread == 0 ) /* If there is no threa given, then we use sequential version */
		tp = newTickParam(0, g->cols - 1, g); /* And said to the main thread to threat all columns */

	while(o.max_tick != 0) {         /* Inifinit loop if total tick not given */
		gamePrintInfo(g, o);         
		
		if ( o.nb_thread == 0 )      /* if there is 0 thread then do not use thread method  */
			gameTick(tp);       	 /* Lets the game tick */
		else
			createNThreadF(o.nb_thread, g, o.use_fine_grained);

		__swapGrid(g);
		--o.max_tick;
		#ifdef PRINT                 /* If we print we add some delay without it we can't see the grid */
			usleep(400000);
		#endif
	}
	
	if ( o.use_ncurses) /* If we use ncurses ( and then init it ) */
		endNCurses();   /* we need to clear display info */

	if ( o.save_file ) 	
		saveBoard(g);

	if ( o.nb_thread == 0 ) 
		free(tp);

	freeGame(g);           /* Free space we are not in Java */
	
	exit(EXIT_SUCCESS);
}

