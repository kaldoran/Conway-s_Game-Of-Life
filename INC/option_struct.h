#ifndef OPTION_STRUCT
#define OPTION_STRUCT

#include <stdbool.h>

typedef struct Option {
	int max_tick;             // How much tick we need to do            - Default : 100
	char* file_path;          // Path to the file to load               - Default : ""
	unsigned int nb_thread;   // Total number of thread to use          - Default : 0 
	unsigned int rows;        // Number of rows to generate             - Default : Random
	unsigned int cols;        // Number of columns to generate          - Default : Random
	bool use_ncurses;         // Do we use ncurses for the display ?    - Default : false
	bool use_fine_grained;    // Do we use fine grain in multi thread ? - Default : false
	bool save_file;           // Do we need to save the last grid ?     - Default : false
} Option;

#endif
