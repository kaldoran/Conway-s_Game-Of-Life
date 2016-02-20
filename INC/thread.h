#ifndef THREAD
#define THREAD

#include <stdbool.h>

#include "game_struct.h"
#include "thread_struct.h"


ThreadInfo *newThreadInfo(unsigned int n, Game *g, bool fine_grained);

void freeThreadInfo(ThreadInfo *ti);

void createTask(ThreadInfo *ti, bool fine_grained);

void runThread(ThreadInfo *ti); 

void createNThread(ThreadInfo *ti);

void endNThread(ThreadInfo *ti); 

#endif
