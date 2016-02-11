#ifndef OPTION_STRUCT
#define OPTION_STRUCT

#include <stdbool.h>

typedef struct Option {
	int max_tick;
	char* file_path;
	unsigned int nb_thread;
	unsigned int rows;
	unsigned int cols;
	bool use_ncurses;
	bool use_fine_grained; 
} Option;

#endif
