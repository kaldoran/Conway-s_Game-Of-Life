#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "option.h"

void usage(char* name) {
	printf("%s [-h]\n\t\t [-f <filePath>] [-t <maxTick>] [-n]\n\n", name);
	printf("\t\t -h : print this help\n");
	printf("\t\t -f filePath : path to the file to use for the grid\n");
	printf("\t\t -t maxTick : max time to make the game tick\n");
	printf("\t\t -n : use ncurses for the display\n");
	
	exit(EXIT_SUCCESS);
}

Option __setDefaultValue() {
	Option o;

	o.use_ncurses = false;
	o.file_path = "\0";
	o.max_tick = -1;
	
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
				fprintf(stderr, "YOLOy");
				break;
			default: 
				exit(EXIT_FAILURE);
		}
	}
	
	if ( argv[optind] == NULL) 
		usage(argv[0]);

	return o;
}

