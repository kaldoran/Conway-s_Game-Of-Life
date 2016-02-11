#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "game.h"
#include "option.h"

void usage(char* name) {
	printf("%s [-h]\n\t\t [-f <filePath>] [-t <maxTick>] [-c <number cols] [-r <number rows] [-g] [-n]\n\n", name);
	printf("\t\t -h : print this help\n");
	printf("\t\t -f filePath : path to the file to use for the grid\n");
	printf("\t\t -t maxTick : max time to make the game tick, set it to negatif for infinite tick\n");
	printf("\t\t -c : total numner of column\n");
	printf("\t\t -r : total number of rows\n");
	printf("\t\t -n : use ncurses for the display\n");
	printf("\t\t -g : if -g set then we use fine grained method\n");

	exit(EXIT_SUCCESS);
}

Option __setDefaultValue() {
	Option o;
	
	o.use_fine_grained = false;
	o.use_ncurses = false;
	o.file_path = "\0";
	o.max_tick = 100;
	o.nb_thread = 0;

	o.rows = rand() % ( MAX_ROWS_SIZE - MIN_ROWS_SIZE) + MIN_ROWS_SIZE;
	o.cols = rand() % ( MAX_COLS_SIZE - MIN_COLS_SIZE) + MIN_COLS_SIZE;	
	
	return o;
}

Option getOption(int argc, char **argv) {
	int opt = 0;
	Option o = __setDefaultValue();
	
	while ( (opt = getopt(argc, argv, OPT_LIST)) != -1 ) {
		switch(opt) {
			case '?':
			case 'h': 
				usage(argv[0]);
				break;
			case 'f':
				if ( optarg != 0 )
					o.file_path = optarg;
				break;
			case 't':
				o.max_tick = atoi(optarg);
				break;
			case 'n': 
				o.use_ncurses = true;
				break;
			case 'p':
				o.nb_thread = MAX(atoi(optarg), 0);
				break;
			case 'r':
				o.rows = MAX(atoi(optarg), MIN_ROWS_SIZE);
				break;
			case 'c':
				o.cols = MAX(atoi(optarg), MIN_COLS_SIZE);
				break;
			case 'g':
				o.use_fine_grained = true;
				break;
			default: 
				exit(EXIT_FAILURE);
		}
	}
	
	if ( argv[optind] == NULL) 
		fprintf(stderr, "Remember to use -h for help\n");

	return o;
}

