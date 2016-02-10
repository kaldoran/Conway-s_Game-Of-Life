#ifndef OPTION_STRUCT
#define OPTION_STRUCT

#include <stdbool.h>

typedef struct Option {
	int max_tick;
	char* file_path;
	bool use_ncurses;
	unsigned int nb_thread;
} Option;

#endif
