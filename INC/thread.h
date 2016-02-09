#ifndef THREAD
#define THREAD

#include "game_struct.h"
#include "thread_struct.h"

pthread_t *creatNThread(int n, Game* g);

#endif
