#ifndef TICK_PARAM_STRUCT
#define TICK_PARAM_STRUCT

#include "game_struct.h"

typedef struct TickParam {
	unsigned int min; /* Where do the thread need to start process cell */
	unsigned int max; /* And where did he need to stop */
	Game *g;          /* Pointer to the board */
} TickParam;
#endif
