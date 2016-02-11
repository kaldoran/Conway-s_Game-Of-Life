#ifndef TICK_PARAM_STRUCT
#define TICK_PARAM_STRUCT

#include "game_struct.h"

typedef struct TickParam {
	unsigned int min;
	unsigned int max;
	Game *g;
} TickParam;
#endif
