#ifndef THREAD_STRUCT
#define THREAD_STRUCT

#include "game_struct.h"

typedef struct threadParam {
	unsigned int min;
	unsigned int max;
	Game *g;
} threadParam;
#endif
