#ifndef THREAD
#define THREAD

#include <stdbool.h>
#include "game_struct.h"

bool createNThreadF(unsigned int n, Game *g, bool fine_grained);

#endif
