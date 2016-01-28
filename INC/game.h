#ifndef GAME_H
#define GAME_H

#include "game_struct.h"

void gamePrint ( Game* g, int (*pf)(const char *, ...));
// void gamePrint ( Game* g, void (*printingFunction)(char *) );

Game* generateRandomBoard();

#endif
