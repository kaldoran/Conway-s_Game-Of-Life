#ifndef OPTION_STRUCT
#define OPTION_STRUCT

typedef struct Option {
	int max_tick;
	char* file_path;
	bool use_ncurses;
} Option;

#endif
